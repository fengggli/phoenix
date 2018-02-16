cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include(cmake/common.cmake)
project(phoenix++)
#add_definitions("-Wall -Wextra")
set(CMAKE_CXX_STANDARD 11)
# use -g and -O3 in different builds DEBUG/RELEASE
set(CMAKE_CXX_FLAGS "-Wall -D_LINUX_  -DMMAP_POPULATE -fstrict-aliasing -Wstrict-aliasing  -D__x86_64__ -pthread")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# google test
enable_testing()
set(GTEST_ROOT "$ENV{HOME}/software/install")
find_package(GTest REQUIRED)
include_directories(GTEST_INCLUDE_DIRS)
#target_link_libraries(binary GTest::GTest GTest::Main)

# intel tbb
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
include_directories(allocator/)
#target_link_libraries(binary GTest::GTest GTest::Main)


include_directories(include)

add_subdirectory(allocator/copager)
add_subdirectory(src)
add_subdirectory(tests)
