add_executable(test_alloc test_alloc.cc)
target_link_libraries(test_alloc GTest::GTest GTest::Main)

add_executable(test_alloc_tbb test_alloc.cc)
find_library(TBB_LIBRARY
        NAMES tbbmalloc
            HINTS "/home/lifen/software/intel/compilers_and_libraries_2018.0.128/linux/tbb/lib/intel64/gcc4.7"
            )
    if(${TBB_LIBRARY} STREQUAL "TBB_LIBRARY-NOTFOUND")
        message(FATAL_ERROR "cannot find tbb")
    endif()
target_compile_definitions(test_alloc_tbb PRIVATE "-DTBB")
target_link_libraries(test_alloc_tbb ${TBB_LIBRARY} GTest::GTest GTest::Main)

add_executable(test_alloc_simple test_alloc.cc)
target_compile_definitions(test_alloc_simple PRIVATE "-DSIMPLE")
target_link_libraries(test_alloc_simple GTest::GTest GTest::Main)

#add_executable(test_alloc_m test_alloc.cc)
#target_compile_definitions(test_alloc_m PRIVATE "-DM_ALLOC")
#target_link_libraries(test_alloc_m GTest::GTest GTest::Main)


