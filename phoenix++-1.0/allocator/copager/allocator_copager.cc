/*
 * Description:
 * provide pager  to the allocator
 *
 * First created: 2018 Mar 01
 * Last modified: 2018 Mar 08
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#include "allocator_copager.h"

#include <api/components.h>
#include <api/pager_itf.h>
#include <api/region_itf.h>
#include <api/block_itf.h>
#include <api/block_itf.h>
#include <api/region_itf.h>
namespace copager_ns{

    static Component::IBlock_device *      _block = nullptr;
    static Component::IPager *             shared_pager = nullptr; //one pager support multiple pmem instance 


    unsigned long NUM_PAGER_PAGES=80; // number of physical pages used by a heap
    unsigned long NUM_BLOCKS=1000; // total blocks shared by all regions(backend of heaps)

    Component::IPager * get_shared_pager(){
        assert(shared_pager);
        return shared_pager;
    }

    void  init_pager(size_t nr_pager_pages, size_t nr_blocks){
        NUM_PAGER_PAGES=nr_pager_pages;
        NUM_BLOCKS=nr_blocks;
        init_pager();
    }
    void  init_pager(){
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
        _block = fact->create("00:06.0", &mask);

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
        config_string += getenv("COMANCHE_HOME");
        config_string += "/blockfile.dat";
        //config_string += "/dev/vda";
        // configf
        //  config_string += "\"}";
        config_string += ("\",\"size_in_blocks\":"+ std::to_string(NUM_BLOCKS)+"}");
        //config_string += "\",\"size_in_blocks\":10000}";
        PLOG("config: %s", config_string.c_str());

        _block = fact_blk->create(config_string);
        assert(_block);
        fact_blk->release_ref();
        PINF("Block-layer component loaded OK (itf=%p)", _block);

#endif

        /* 
         * instantiate pager
         */

        assert(_block);

        comp = load_component("libcomanche-pagersimple.so",
                Component::pager_simple_factory);
        assert(comp);
        IPager_factory * fact_pager = static_cast<IPager_factory *>(comp->query_interface(IPager_factory::iid()));
        assert(fact_pager);
        shared_pager = fact_pager->create(NUM_PAGER_PAGES,"unit-test-heap",_block, true);
        assert(shared_pager);

        PINF("Pager-simple component loaded OK.");
    }



    void destroy_pager(){
        assert(_block);
        //assert(!shared_pager);
        _block->release_ref();
    }
}

