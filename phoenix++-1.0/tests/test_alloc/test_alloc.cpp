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

#include <mcheck.h>
#include <gtest/gtest.h>

#include <memory>
#include <iostream>
#include <vector>

#include "allocator_chooser.h"
#include "stddefines.h"


using namespace std;

/*
 * test basic use of allocator
 */
TEST(AllocatorTest, ByteRead){
    
    ALLOCATOR<char> alloc;
    int fd;
    struct stat finfo;
    int ret;

    char const *fname = "/home/lifeng/phoenix/phoenix++-1.0/data/histogram_datafiles/XING_B24.BMP";
    CHECK_ERROR((fd = open(fname, O_RDONLY)) < 0);
    // Get the file info (for file length)
    CHECK_ERROR(fstat(fd, &finfo) < 0);



    auto const p= alloc.allocate(4096*20); // 20 pages 
    

    memset(p, 0x0, 20*4096);
    ret = read (fd, p, 2048);// finfo.st_size);
    printf("ret = %d, finfo size = %ld, read at %p\n", ret, finfo.st_size, p);

    CHECK_ERROR (close (fd) < 0);

    //alloc.construct(q++); // empty constructor
    alloc.deallocate(p, 5);
}

#if 0
/*
 * test basic use of allocator
 */
TEST(AllocatorTest, Basic){
    
    ALLOCATOR<string> alloc;

    auto const p= alloc.allocate(5); // allocate n unconstructed strings

    auto q = p;
    //alloc.construct(q++); // empty constructor
    alloc.construct(q++, 10, 'c');// empty constructor
    alloc.construct(q++, "hello");// empty constructor

    cout << *p <<endl;
    //cout << *q <<endl; // this is a disaster! not constructed

    // need call destroy
    //alloc.destroy(p, 5);
    while(q != p){
        alloc.destroy(--q);
    }
    alloc.deallocate(p, 5);
}

/*
 * test allocator copy
 */
TEST(AllocatorTest, Copy){
    ALLOCATOR<int> alloc;


    vector<int> vi(10); // vector of 10 int
    auto p = alloc.allocate(vi.size()*2);

    auto q = uninitialized_copy(vi.begin(), vi.end(), p);
    uninitialized_fill_n(q, vi.size(), 42);

    while(q!= p){
        alloc.destroy(--q);
    }
    alloc.deallocate(p, vi.size()*2);
}

TEST(AllocatorTest, Vector){
    vector<int, ALLOCATOR<int>> vi;

    std::cout << "vector increasing start" <<std::endl;
    for(auto i = 0; i <50; i++){
        vi.push_back(i);
        std::cout << "inserted"<< i <<std::endl;
    }
    std::cout << "vector increasing end" <<std::endl;
}


#endif

int main(int argc, char *argv[]){
    //mtrace();

/*    test_simple();*/
    //test_copy();

#ifdef COPAGER
    //init_pager(32000, 30000);
    init_pager();
#endif

    ::testing::InitGoogleTest(&argc, argv);

auto r = RUN_ALL_TESTS();

#ifdef COPAGER
    destroy_pager();
#endif

    //muntrace();

    return r;
}

