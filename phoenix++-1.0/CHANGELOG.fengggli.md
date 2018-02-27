# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

Last modified: 2018 Jan 26
Feng Li(fengggli@yahoo.com)

##2018 Feb 27
[note]: 
    1. numbers(MB != MiB):
        nr_huge pages : 1000*2M = 2G
        nr_physic_pages: 2G/4k= ~500K pages (get from huge page)
        nr_blocks: 8G/4k = 2M blocks(max heap size)
        
        

##2018 Feb 21
[note]:
    1. in pmem module(with simple pager), the virtual and physical mem have the same size.
    2. replacement policy:
        * each time evict NO. access_num%phys_num.
        * I assume it I have a sequential access(over and over again, there won't be fault when all pages are mapped!(verified)
[TODO]: 
    1. open a p\_mem\_t: 

##2018 Feb 20
[fixed]:
    1. fix broken pager, now kmeans works
[NOTE]:
    1.  larger input for kmeans:
    Simple_pager_component::create-> blk->allocate_io_buffer->phsyical memory:: allocate io_buffer_t
    2. physical pages are the same size with slab size(where are those regions?)
        region::_table, each entry(virt_addr start, virt_addr end, blk_itf)
        what does the "flush"?
    3. in the pmem\_component: the virtual memory and physical memory size are the same! window size 
[questions]:
    1. if an application use multiple piece of pmem, how it should be like?
        multiple Pmem_paged_component, backed by the same "pager", see the __global_inst_v in pmem_paged.cpp
        Cthe all copager-allocators will have reference to the same pager!
    2. get clear of phys pages and virtual pages!
[TODO]:
    1. different allocators will open different regions on the same pager
    2. get timing for kmeans in emulated devices
    3. use different build_dir of comanche for different usuage!(too much output for each physical pages mapping)

##2018 Feb 19
[NOTES]:
    0. paged example: "Exception:async\_write: out of bounds" if n\_elemts = 300000(original is 32768)
        * even in kmeans example, DEF_NUM_POINTS(100000-> 100000)  removes the error
    1. pmem::open->
                 ->Region_manager::reuse_or_allocate_region

                    -> _region_table.allocate
                        64 = _table->entries[i].size
                        64= size_in_blocks
                    -> return new Region_session(_lower_block_layer,
                            id.c_str(),
                            rd->saddr,
                            rd->saddr + rd->size - 1);
    2. if a slab\_size if different from the previously one shoudl give an exception!
       eg: n_elem_sizes doubles however the same region is found, size(of blocks) remains as before
        should use a different name for this region
    3. serveral of the applications uses the mmap to read file. it should be equivelent for pmem allocated memory.
        * regular mmap
            load when needed
        * pmem module
            1. read all info into pmem
            2. swap in/out during runtime
    4. For pager\_factory::create, can pass in a force\_init=true to erase all the regions!

[Question]:
    1. test1.cpp: config\_string: 10000?
    2. region\_session: for pmem test and 32768 n\_element, region session: 1~64(64\*4k blocks)


##2018 Feb 16
[NOTES]:
    0. kmeans allocation is tained....
    1. need to track all the pages(save all handlers?)
        * can use p to hash get the  handle
        * maintain a map to get the handler
    2. try the copager example in phoenix source tree
    3. make sure 

[fixed]:
    1. cannot have seprate implementation file for template classes
[added]:
    2. add copager constructor and deconstructor
    1. example pmem example is added in source tree using /dev/vda
[TODO]:
    1. allocation function
    2. FIND_COMANCHE.cmake?

##2018 Feb 15
[added]:
	1. all data set are extracted in data/
    2. add cmakelist for all applications
    3. tried all applications
    4. a scripts to run all applications
[note]:
    1. even "large" data set in the example is less than 2GB(histogram-large.bmp, 1.4G).
    2. kmeans construct random data in memory, however for the other applications, use usually mmap to a file to get the input, for copager-allocator, each allocation will envoke a mmap systemcall
[todo]:
    applications:
        replace the allocators
    comanche:
        cmake externel files
        need sudo even for file blockposix

##2018 Feb 12
[added]:
	1. kmeans interface now is fixed, application side will call allocator
[TODO]:
	1. hook with allocator

## 2018 Jan 2
[TODO]:
    0. verify simple_alloc works, how it grows with increasing size?
        the kmeans use point combiner, which doens't use Allocator
    1. use the simple_alloc as a wrapper for block_allocator 
    2. MUST_REDUCE in combiner.h controls how associate_combiner behaves




