/*
 * Description:
 *  a test program of std::allocator
 *
 * First created: 2018 Feb 05
 * Last modified: 2018 Mar 02
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory.h>
#include <unistd.h>

#include <mcheck.h>

#include <memory>
#include <iostream>
#include <vector>

#include "allocator_chooser.h"
#include "stddefines.h"
#include <cstring>

//#define NO_MMAP

using namespace std;



int main(int argc, char *argv[]){
    //mtrace();

/*    test_simple();*/
    //test_copy();

#ifdef COPAGER
    //init_pager(32000, 30000);
    init_pager();
#endif
    ALLOCATOR<char> alloc;
    int fd;
    struct stat finfo;
    int ret;
    const constexpr size_t io_sz = 4096*20;

    char const *fname = "/home/lifeng/phoenix/phoenix++-1.0/data/histogram_datafiles/XING_B24.BMP";
    CHECK_ERROR((fd = open(fname, O_RDONLY)) < 0);
    // Get the file info (for file length)
    CHECK_ERROR(fstat(fd, &finfo) < 0);

    auto const p= alloc.allocate(io_sz); // 20 pages 

    printf("the first byte: %d at %p\n", *p, p);
    memset(p, 0x0, io_sz);
    printf("the first byte: %d\n", *p);

#ifndef NO_MMAP
    char *fdata2;
    CHECK_ERROR((fdata2 = (char*)mmap(0, finfo.st_size + 1, 
        PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0)) == NULL);

#else

    char *fdata2 = (char *)malloc (finfo.st_size);
    
    ret = read (fd, fdata2, io_sz);// finfo.st_size);
    printf("ret = %d, finfo size = %ld, read at %p\n", ret, finfo.st_size, p);


#endif
    std::memcpy(p, fdata2, io_sz);
    CHECK_ERROR (close (fd) < 0);
    //alloc.construct(q++); // empty constructor
    alloc.deallocate(p, 5);



#ifdef COPAGER
    destroy_pager();
#endif

    //muntrace();


    return 0;
}

