/*
 * Description:
 * a simple allocator
 * https://stackoverflow.com/questions/826569/compelling-examples-of-custom-c-allocators
 *
 * First created: 2018 Feb 06
 * Last modified: 2018 Mar 01
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#ifndef SIMPLE_ALLOC_H_
#define SIMPLE_ALLOC_H_
#include <memory>
#include <iostream>


namespace simple_allocator_namespace
{
        template <typename T>
        class simple_allocator: public std::allocator<T>
        {

            private:
            static constexpr bool option_DEBUG = true;
public:
                typedef size_t size_type;
                typedef T* pointer;
                typedef const T* const_pointer;

                template<typename _Tp1>
                struct rebind
                {
                        typedef simple_allocator<_Tp1> other;
                };

                pointer allocate(size_type n, const void *hint=0)
                {
                    if(option_DEBUG){
                    std::cerr<<"Alloc "<<n*sizeof(T) << " bytes"<< std::endl;
                    }
                    return std::allocator<T>::allocate(n, hint);
                }

                void deallocate(pointer p, size_type n)
                {
                    if(option_DEBUG){
                        std::cerr << "Dealloc "<<n*sizeof(T) << " bytes at "  << (void *)p << std::endl;
                    }
                    return std::allocator<T>::deallocate(p, n);
                }

                simple_allocator() throw(): std::allocator<T>() { std::cerr << "[simpleAllocator]: Hello allocator!\n" <<std::endl; }
                simple_allocator(const simple_allocator &a) throw(): std::allocator<T>(a) { }
                template <class U>                    
                simple_allocator(const simple_allocator<U> &a) throw(): std::allocator<T>(a) { }
                ~simple_allocator() throw() {std::cerr << "[simpleAllocator]: Bye allocator!" <<std::endl; }
        };
}

#endif

