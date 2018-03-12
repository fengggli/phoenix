#cmake_minimum_required (VERSION 3.5.1 FATAL_ERROR)

#project(pmem-posix-tests CXX)

#find_library(GTEST_LIB NAMES GTEST PATHS /usr/local/lib,/usr/lib)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS} -DCONFIG_DEBUG)

add_library(allocator-copager SHARED  allocator_copager.cc)

add_library(allocator-copager-nvme SHARED  allocator_copager.cc)
target_compile_definitions(allocator-copager-nvme PRIVATE "-DUSE_SPDK_NVME_DEVICE")
#add_executable(allocator-pmem-exe allocator_copager.cc)
#target_link_libraries(allocator-pmem common numa gtest pthread dl comanche-pmempaged)
#target_compile_features(allocator-pmem PRIVATE cxx_range_for)

add_executable(pmem-posix-test test1.cpp)
target_link_libraries(pmem-posix-test common numa gtest pthread dl comanche-pmempaged)
target_compile_features(pmem-posix-test PRIVATE cxx_range_for)
#target_link_libraries(pmem-posix common numa gtest pthread dl comanche-pmempaged)
#target_compile_features(pmem-posix PRIVATE cxx_range_for)
