add_executable(test_alloc test_alloc.cc)
target_link_libraries(test_alloc GTest::GTest GTest::Main)

add_executable(test_alloc_tbb test_alloc.cc)
target_compile_definitions(test_alloc_tbb PRIVATE "-DTBB")
target_link_libraries(test_alloc_tbb ${TBB_LIBRARY} GTest::GTest GTest::Main)

add_executable(test_alloc_simple test_alloc.cc)
target_compile_definitions(test_alloc_simple PRIVATE "-DSIMPLE")
target_link_libraries(test_alloc_simple GTest::GTest GTest::Main)

#add_executable(test_alloc_m test_alloc.cc)
#target_compile_definitions(test_alloc_m PRIVATE "-DM_ALLOC")
#target_link_libraries(test_alloc_m GTest::GTest GTest::Main)


