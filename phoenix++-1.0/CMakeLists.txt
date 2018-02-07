cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

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

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
