/*
 * Description:
 *
 * First created: 2018 Mar 01
 * Last modified: 2018 Mar 01
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#ifndef ALLOCATOR_CHOOSER_H_
#define ALLOCATOR_CHOOSER_H_

#define NO_MMAP // if you explicitily use allocator, do not utilize the mmap in some of phoenix applications

#ifdef TBB
#include "tbb/scalable_allocator.h"
template<typename T>
using ALLOCATOR = tbb::scalable_allocator<T>;
#elif defined(SIMPLE)
#include "simple/allocator_simple.h"
template<typename T>
using ALLOCATOR = simple_allocator_namespace::simple_allocator<T>;
#elif defined(COPAGER)
#include "copager/allocator_copager.h"
using namespace copager_ns;
template<typename T>
using ALLOCATOR = allocator_copager<T>;

#else
template<typename T>
#undef NO_MMAP
using ALLOCATOR = std::allocator<T>;
#endif



#endif
