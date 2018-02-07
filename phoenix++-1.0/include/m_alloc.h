/*
 * Description:
 *
 * First created: 2018 Feb 05
 * Last modified: 2018 Feb 06
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 */

#ifndef M_ALLOCATOR_H_
#define M_ALLOCATOR_H_

#include <cstdlib>
#include <new>
#include <iostream>

template <class T>
struct Mallocator {
  typedef T value_type;
  Mallocator(){std::cout << "my simple allocation is called";};
  template <class U> constexpr Mallocator(const Mallocator<U>&) noexcept {}
  [[nodiscard]] T* allocate(std::size_t n) {
    if(n > std::size_t(-1) / sizeof(T)) throw std::bad_alloc();
    std::cerr<<"use my simple allocation!" << std::endl;
    if(auto p = static_cast<T*>(std::malloc(n*sizeof(T)))) return p;
    throw std::bad_alloc();
  }
  void deallocate(T* p, std::size_t) noexcept { std::free(p); }
};
template <class T, class U>
bool operator==(const Mallocator<T>&, const Mallocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const Mallocator<T>&, const Mallocator<U>&) { return false; }

#endif
