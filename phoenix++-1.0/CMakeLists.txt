cmake_minimum_required(VERSION 3.5)
include(cmake/common.cmake)

project(phoenix++)

option(has_tbb "has tbb installed" off)

# google test
enable_testing()
set(GTEST_ROOT "$ENV{HOME}/software/install")
find_package(GTest REQUIRED)
include_directories(GTEST_INCLUDE_DIRS)

# intel tbb, diabled by default
if(has_tbb)
    set(TBB_PREFIX "/home/lifen/software/intel/compilers_and_libraries_2018.0.128/linux/tbb")
    FIND_PATH(TBB_INCLUDE_DIR tbb/scalable_allocator.h HINTS
      ${TBB_PREFIX}/include/
      /usr/include/
      /usr/local/include/
      /opt/local/include/
    )

    find_library(TBB_LIBRARY
        NAMES tbbmalloc
            HINTS "${TBB_PREFIX}/lib/intel64/gcc4.7"
            )
    if(${TBB_LIBRARY} STREQUAL "TBB_LIBRARY-NOTFOUND")
        message(FATAL_ERROR "cannot find tbb")
    endif()
    include_directories(${TBB_INCLUDE_DIR})
endif(has_tbb)

# comanche
#TODO: use findpackage interface
include(cmake/FindComanche.cmake)

include_directories(allocator/)

include_directories(include)

add_subdirectory(allocator/copager)
add_subdirectory(src)
add_subdirectory(tests)
