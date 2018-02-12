/*
 * Description:
 *  a test program of std::allocator
 *
 * First created: 2018 Feb 05
 * Last modified: 2018 Feb 07
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#include <mcheck.h>
#include <gtest/gtest.h>

#include <memory>
#include <iostream>
#include <vector>

#ifdef TBB
#include "tbb/scalable_allocator.h"

#elif defined M_ALLOC
#include "m_alloc.h"

#elif defined SIMPLE
#include "simple_alloc.h"

#endif


using namespace std;

/*
 * test basic use of allocator
 */
TEST(AllocatorTest, Basic){
    
#ifdef TBB
#warning "use tbb"
    tbb::scalable_allocator<string> alloc;
#elif defined SIMPLE
    #warning "use simple"
    simple_allocator_namespace::simple_allocator<string> alloc;
#else
    allocator<string> alloc;
#endif

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
#ifdef TBB
#warning "use tbb"
    tbb::scalable_allocator<int> alloc;
#elif defined SIMPLE
    #warning "use simple"
    simple_allocator_namespace::simple_allocator<int> alloc;
    //Mallocator<int> alloc;
#else
    allocator<int> alloc;
#endif


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
#ifdef TBB
#warning "use tbb"
    vector<int,tbb::scalable_allocator<int>> vi;
#elif defined SIMPLE
    #warning "use simple"
    vector<int, simple_allocator_namespace::simple_allocator<int>> vi;
#else
    vector<int> vi;
#endif

    std::cout << "vector increasing start" <<std::endl;
    for(auto i = 0; i <50; i++){
        vi.push_back(i);
        std::cout << "inserted"<< i <<std::endl;
    }
    std::cout << "vector increasing end" <<std::endl;
}



int main(int argc, char *argv[]){
    //mtrace();

/*    test_simple();*/
    //test_copy();

    ::testing::InitGoogleTest(&argc, argv);

auto r = RUN_ALL_TESTS();

    //muntrace();

    return r;
}

