/*
 * Description: 
 *  a wrapper for pmem using std::allocator interface *  reference: comanche/src/components/experimental/pmem-paged/unit_test/test1.cpp
 *
 * First created: 2018 Feb 13
 * Last modified: 2018 Feb 19
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#ifndef ALLOCATOR_COPAGER_H_
#define ALLOCATOR_COPAGER_H_

#include <string>
#include <list>
#include  <utility>
#include <map>
#include <common/cycles.h>
#include <common/exceptions.h>
#include <common/str_utils.h>
#include <common/logging.h>
#include <common/cpu.h>
#include <common/utils.h>

#include <component/base.h>

#include <api/components.h>
#include <api/block_itf.h>
#include <api/region_itf.h>
#include <api/pager_itf.h>
#include <api/pmem_itf.h>


#include <memory>
#include <iostream>

#include <api/block_itf.h>
#include <api/region_itf.h>
#include <api/pager_itf.h>
#include <api/pmem_itf.h>




// from comanche copager-pmem


namespace allocator_copager_namespace
{
    using namespace Component;
    template <typename T>
        class allocator_copager: public std::allocator<T>
    {
        public:
            typedef size_t size_type;
            typedef T* pointer;
            typedef const T* const_pointer;

            template<typename _Tp1>
                struct rebind
                {
                    typedef allocator_copager<_Tp1> other;
                };

            /*
             * allocate space from pmem
             */
            pointer allocate(size_type n, const void *hint=0);
            /*
             * free space from pmem
             */
            void deallocate(pointer p, size_type n);


            /*
             * prepare environment for pmem
             */
            allocator_copager() throw(); 
            allocator_copager(const allocator_copager &a) throw(): std::allocator<T>(a) { }
            template <class U>                    
                allocator_copager(const allocator_copager<U> &a) throw(): std::allocator<T>(a) { }

            /*
             * tear down environment for pmem
             */
            ~allocator_copager() throw();
        private:

            Component::IBlock_device *      _block;
            Component::IPager *             _pager;
            Component::IPersistent_memory * _pmem;
            std::map<pointer,IPersistent_memory::pmem_t > _handlers; //  need to find the handler to free a piece of memory
            uint64_t nr_elems = 0; // number of elems of this allocator instance
            //TODO: reused can be also in this map
    };

    template <typename T>
        T* allocator_copager<T>::allocate(size_type n, const void *hint)
        {
            PINF("Prepare to allocate %lu bytes, current nr_elems = %d", n*sizeof(T), nr_elems);

            pointer p = nullptr;
            size_t slab_size = n* sizeof(T);
            bool reused;
#ifdef DEBUG
            std::cerr<<"Alloc "<<n*sizeof(T) << " bytes"<< std::endl;
#endif

            std::string pmem_name = "test_1";
            //pmem_name += std::to_string(nr_elems);
            //nr_elems+= n;

            IPersistent_memory::pmem_t handle = _pmem->open(pmem_name, slab_size, NUMA_NODE_ANY, reused, (void*&)p);

            PLOG("handle: %p", handle);
            assert(p!=nullptr);

            /* 0xf check */
            for(unsigned long e=0;e<n;e++)
                p[e] = 0xf;

            PINF("0xf writes complete. Starting check...");

            for(unsigned long e=0;e<n;e++) {
                if(p[e] != 0xf) {
                    PERR("Bad 0xf - check failed!, value is %d", p[e]);
                    assert(0);
                }
            }
            PMAJOR("> 0xf check OK!");


            memset(p,0,slab_size);
            PINF("Zeroing complete.");
            //return std::allocator<T>::allocate(n, hint);
            _handlers.insert(std::make_pair(p, handle));
            return p;
        }
    template <typename T>
        void allocator_copager<T>::deallocate(pointer p, size_type n)
        {
#ifdef DEBUG
            std::cerr << "Dealloc "<<n*sizeof(T) << " bytes at "  << p << std::endl;
#endif
            auto it = _handlers.find(p);
            if(it != _handlers.end()){
                IPersistent_memory::pmem_t handle = it->second;
                _pmem->close(handle);
            }
            else{
                std::cerr << "try to deallocate a invalide space"  << p << std::endl;
                assert(1);
            }
            //return std::allocator<T>::deallocate(p, n);
        }

    template <typename T>
        allocator_copager<T>::allocator_copager() throw(): std::allocator<T>(){ 
            std::cerr << "[simpleAllocator]: Hello allocator!\n" <<std::endl; 

            Component::IBase * comp;
            /*
             * instantialize block device
             */
#ifdef USE_SPDK_NVME_DEVICE

            comp = Component::load_component("libcomanche-blknvme.so",
                    Component::block_nvme_factory);

            assert(comp);
            PLOG("Block_device factory loaded OK.");
            IBlock_device_factory * fact = (IBlock_device_factory *) comp->query_interface(IBlock_device_factory::iid());

            cpu_mask_t mask;
            mask.add_core(2);
            _block = fact->create("8b:00.0", &mask);

            assert(_block);
            fact->release_ref();
            PINF("Lower block-layer component loaded OK.");

#else

            comp = Component::load_component("libcomanche-blkposix.so",
                    Component::block_posix_factory);
            assert(comp);
            PLOG("Block_device factory loaded OK.");

            IBlock_device_factory * fact_blk = (IBlock_device_factory *) comp->query_interface(IBlock_device_factory::iid());
            std::string config_string;
            config_string = "{\"path\":\"";
            //  config_string += "/dev/nvme0n1";
            // config_string += "./blockfile.dat";
            config_string += "/dev/vda";
            // configf
            //  config_string += "\"}";
            config_string += "\",\"size_in_blocks\":10000}";
            PLOG("config: %s", config_string.c_str());

            _block = fact_blk->create(config_string);
            assert(_block);
            fact_blk->release_ref();
            PINF("Block-layer component loaded OK (itf=%p)", _block);

#endif

            /* 
             * instantiate pager
             */
#define NUM_PAGER_PAGES 128

            assert(_block);

            comp = load_component("libcomanche-pagersimple.so",
                    Component::pager_simple_factory);
            assert(comp);
            IPager_factory * fact_pager = static_cast<IPager_factory *>(comp->query_interface(IPager_factory::iid()));
            assert(fact_pager);
            _pager = fact_pager->create(NUM_PAGER_PAGES,"unit-test-heap",_block);
            assert(_pager);

            PINF("Pager-simple component loaded OK.");

            /*
             * instantiate pmem
             */
            assert(_pager);

            comp = load_component("libcomanche-pmempaged.so",
                    Component::pmem_paged_factory);
            assert(comp);
            IPersistent_memory_factory * fact_pmem = static_cast<IPersistent_memory_factory *>
                (comp->query_interface(IPersistent_memory_factory::iid()));
            assert(fact_pmem);
            _pmem = fact_pmem->open_allocator("testowner",_pager);
            assert(_pmem);
            fact_pmem->release_ref();

            _pmem->start();
            PINF("Pmem-pager component loaded OK.");

        }

    template <typename T>
        allocator_copager<T>::~allocator_copager() throw() {
            std::cerr << "[simpleAllocator]: Bye allocator!" <<std::endl; 
            assert(_pmem);
            assert(_block);

            _pmem->stop();
            _pmem->release_ref();
            _pager->release_ref();
            _block->release_ref();

        }
}

#endif
