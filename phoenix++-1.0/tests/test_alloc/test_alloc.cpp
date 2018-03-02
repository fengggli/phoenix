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

#include <mcheck.h>
#include <gtest/gtest.h>

#include <memory>
#include <iostream>
#include <vector>

#include "allocator_chooser.h"


using namespace std;

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



int main(int argc, char *argv[]){
    //mtrace();

/*    test_simple();*/
    //test_copy();

#ifdef COPAGER
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

