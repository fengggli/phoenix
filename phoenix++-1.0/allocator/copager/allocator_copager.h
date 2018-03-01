/*
 * Description: 
 *  a wrapper for pmem using std::allocator interface *  reference: comanche/src/components/experimental/pmem-paged/unit_test/test1.cpp
 *
 * First created: 2018 Feb 13
 * Last modified: 2018 Mar 01
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
#include <api/pager_itf.h>
#include <api/pmem_itf.h>


#include <memory>
#include <iostream>
#include <string>

#include <api/pager_itf.h>
#include <api/pmem_itf.h>

// from comanche copager-pmem

namespace copager_ns
{
    using namespace Component;

    Component::IPager * get_shared_pager();
    /*
     * init_pager
     */
    void  init_pager();

    /*
     *
     */
    void destroy_pager();

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

            //Component::IBlock_device *      _block;
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
            PINF("Alloc %lu bytes", n*sizeof(T));

            std::string pmem_name = std::string("slab_type_") + typeid(T).name();
            //pmem_name += std::to_string(nr_elems);
            //nr_elems+= n;

            IPersistent_memory::pmem_t handle = _pmem->open(pmem_name, slab_size, NUMA_NODE_ANY, reused, (void*&)p);
\
            PLOG("handle: %p", handle);
            assert(p!=nullptr);

            /* 0xf check */
#ifdef MUST_CHECK_PMEM
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

#endif

            //memset(p,0,slab_size);
            PINF("Zeroing complete.");
            //return std::allocator<T>::allocate(n, hint);
            _handlers.insert(std::make_pair(p, handle));
            return p;
        }
    template <typename T>
        void allocator_copager<T>::deallocate(pointer p, size_type n)
        {
            PINF("Dealloc %lu bytes at %p", n*sizeof(T), p);
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
            PINF("[simpleAllocator]: Hello allocator!\n"); 

           /*
             * instantiate pmem
             */

            Component::IBase * comp;
            _pager = get_shared_pager(); // we only use one pager
            PINF("Pager at %p", _pager);
            assert(_pager); 

            comp = load_component("libcomanche-pmempaged.so",
                    Component::pmem_paged_factory);
            assert(comp);
            IPersistent_memory_factory * fact_pmem = static_cast<IPersistent_memory_factory *>
                (comp->query_interface(IPersistent_memory_factory::iid()));
            assert(fact_pmem);

            /* another function to initiate pager */
            _pmem = fact_pmem->open_allocator("testowner",_pager);
            assert(_pmem);
            fact_pmem->release_ref();

            _pmem->start();
            PINF("Pmem-pager component loaded OK.");

        }

    template <typename T>
        allocator_copager<T>::~allocator_copager() throw() {
            PINF("[CopagerAllocator]: Bye allocator!"); 
            assert(_pmem);

            _pmem->stop();
            _pmem->release_ref();
            _pager->release_ref();

        }
}

#endif
