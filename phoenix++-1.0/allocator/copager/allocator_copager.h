/*
 * Description: 
 *  a wrapper for pmem using std::allocator interface
 *  reference: comanche/src/components/experimental/pmem-paged/unit_test/test1.cpp
 *
 * First created: 2018 Feb 13
 * Last modified: 2018 Feb 13
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#ifndef ALLOCATOR_COPAGER_H_
#define ALLOCATOR_COPAGER_H_

#include <memory>
#include <iostream>

// from comanche copager-pmem


namespace allocator_copager_namespace
{
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
                pointer allocate(size_type n, const void *hint=0)
                {
#ifdef DEBUG
                    std::cerr<<"Alloc "<<n*sizeof(T) << " bytes"<< std::endl;
#endif
                        return std::allocator<T>::allocate(n, hint);
                }

                /*
                 * free space from pmem
                 */
                void deallocate(pointer p, size_type n)
                {
#ifdef DEBUG
                    std::cerr << "Dealloc "<<n*sizeof(T) << " bytes at "  << p << std::endl;
#endif
                        return std::allocator<T>::deallocate(p, n);
                }

                /*
                 * prepare environment for pmem
                 */
                allocator_copager() throw(): std::allocator<T>() { std::cerr << "[simpleAllocator]: Hello allocator!\n" <<std::endl; }
                allocator_copager(const allocator_copager &a) throw(): std::allocator<T>(a) { }
                template <class U>                    
                allocator_copager(const allocator_copager<U> &a) throw(): std::allocator<T>(a) { }

                /*
                 * tear down environment for pmem
                 */
                ~allocator_copager() throw() {std::cerr << "[simpleAllocator]: Bye allocator!" <<std::endl; }
        };
}

#endif
