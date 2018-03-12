# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

Last modified: 2018 Jan 26
Feng Li(fengggli@yahoo.com)

## 2018 Mar 9
[TODO]:
	1. finalize the code!

## 2018 Mar 8
[target]:
	1. try to finalize the 3 applications with scripts(swapping and copaging)
	2. more writing in the draft
[notes]:
	1. I can have multiple nvme emulator !
	2. use fio to get the raw speed
	3. can be backed by regular file or raw device
[new]:
	1. use tmpfs as nvme emulator backend gives same latency and throughput
	2. don't have enough time, just use the file backed nvme!
[result]:
    1. use swap partition
	

## 2018 Mar 7
[qemu]:
    1. i might try to use openchannel qemu instead
	2. now qemu can emulate nvme with 4k block
[comanche block]:
	1. qemu need specify cpu type
	2. now use 4096 block same as real device
[results]:
	1. blk-nvme-test1:
	```
	[ RUN      ] Block_nvme_test.WriteThroughput
	took 291460 cycles (121.441666 usec) per IOP
	rate: 8.234406 KIOPS
	```

## 2018 Mar 6
[exp design]: 
    1. random vs sequential  access: /tmp/ycmd_53723_stdout_kmcjmqsr.log
    2. malloc test
    3. phoenix with example
[limitations]:
    1. no thread supported
    2. compare with allocators?(tcmalloc, glibcmalloc)?(compare single thread with )
    3. should state how is it different from using linux swapping with nvme block device directly
[new software]:
    1. new version of qemu is installed in ${HOME}/software/install

## 2018 Mar 4
[note]:
    [ ]: 10000 pages 120
[apps]:
    [x] kmeans
    [x] histogram
    [x] linear\_regession(large memory size)
[Focus]:
    1. io memory 256M is ok.
    2. make paging faster?
    3. stick with the the above three applications
    4. design the experiment

##2018 Mar 1
[apps]:
    1. linear\regression:108490822 bytes: 120000pages: io memory exceed 256M(API defined memory limit 256 MB)
[steps]:
    1. add ifdef(CUMSTOM\_ALLOC) in source code
    2. add copager\_init and destroy
    3. try simple pager get the size first
[issues]:
    1. issue 1(test\_allocate)
            ret=-1 when read size =2048
[note]:
    1. quick try:
        map 20 pages manually and call "read"
    2. I cannot use gdb to debug:
        https://stackoverflow.com/questions/654393/examining-mmaped-addresses-using-gdb
    3. extra copy helps. I just cannot use posix read into a io memory
    4. I can also mmap first and then copy to my heap.(use MMAP_POPULATE?): after the mempcy all the data is backed by persistent mem: it's okay!
    5. api defined memory need to be larger

##2018 Mar 1
[issues]:
    1. histogram: read 1024bytes ok/ failed at 2048bytes
    2. trace back: 0xf check failed(fixed: char(0xff))
[done]:
    1. now pager creation is  seperated
        * ultimately, _pager will be a "service"
        * each application will open a "pmem"
        * application decide how many region it want(in my case, each type is a "region")
    2. data fetching scripts
    3. results now saved in separate dir
    4. new dataset XING\_B204, will use 29 pages: error
[work]:
    [x] different datatypes
    [ ] applications
    [ ] add prefetch

##2018 Feb 28
[note]:
     
    0. thought:
        * relation: NUM_PAGER_PAGES-num_faults-timing
        * use nvme emulator(cannot otherwise use 4k sector size, I haven't accomplished that in qemu)
            kmeans-small: 240pages?(512B pages instread of 4k)
        * other replacement polocy?
        * replacement policy:
            cannot get access history!(only trigger by faults! if it is)
            prefetch policy
            mL machined? Keep track of faults happened?(run several iterations, train and procceed)
        * Prefetch
        * Fault happens. Read a large chunk of pages?
        * https://www.usenix.org/legacy/event/fast07/tech/full_papers/gill/gill_html/node12.html

    1. exp
      * kmeans(small):
        * data:(use int!)
            10000 points(): 10000*3*4 bytes = 120 000 bytes
            120000/4096 =29.x ~=30 pages(very slow)
        * case(NUM_PAGER_PAGES=64, NUM_BLOCKS=1000)
            only 30 swapping happens
            ok
        * case(NUM_PAGER_PAGES=16, NUM_BLOCKS=1000)
            swapping happens all the time
        * case(NUM_PAGER_PAGES=28, NUM_BLOCKS=1000)
            durable: (faults happens much less frequently)

      * kmeans(midum):
            NUM_PAGER_PAGERS=1024, NUM_BLOCKS=4096
            700000 points 8400 000 bytes
            2050 pages
            slow!

        
##2018 Feb 27
[note]: 
    1. numbers(MB != MiB):
        nr_huge pages : 1000*2M = 2G
        nr_physic_pages: 2G/4k= ~500K pages (get from huge page)
        nr_blocks: 8G/4k = 2M blocks(max heap size)
    2. kmeans is slow if using FORCE\_SYNC
    3. steps:
        1. make kmeans robust:
            * different acess size
            * multiple data types
        2. other applications
            * test the interface correspondingly

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
    3. use different build\_dir of comanche for different usuage!(too much output for each physical pages mapping)

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




