# set compiler flags, etc

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()


# generate compiler lines which can be read by clang parser
set(CMAKE_EXPORT_COMPILE_COMMANDS on) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# path to find Findxx.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# use -g and -O3 in different builds DEBUG/RELEASE
set(CMAKE_CXX_FLAGS "-Wall -D_LINUX_  -DMMAP_POPULATE -fstrict-aliasing -Wstrict-aliasing  -D__x86_64__ -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DCONFIG_DEBUG")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Release build.")
else()
  message("-- ${CMAKE_CURRENT_SOURCE_DIR} > Defaulting to debug build")
  set(CMAKE_BUILD_TYPE Debug)
endif()
