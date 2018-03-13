# use different allocators to generate different binaries
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} rt phoenix)

if(TBB_INCLUDE_DIR)
    add_executable(${PROJECT_NAME}_tbb ${PROJECT_NAME}.cpp)
    target_link_libraries(${PROJECT_NAME}_tbb gtest)
    target_link_libraries(${PROJECT_NAME}_tbb ${TBB_LIBRARY} rt phoenix)
    target_compile_definitions(${PROJECT_NAME}_tbb PRIVATE "-DTBB")
endif(TBB_INCLUDE_DIR)

add_executable(${PROJECT_NAME}_simple ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME}_simple gtest)
target_link_libraries(${PROJECT_NAME}_simple rt phoenix)
target_compile_definitions(${PROJECT_NAME}_simple PRIVATE "-DSIMPLE")

# use block-posix
add_executable(${PROJECT_NAME}_copager ${PROJECT_NAME}.cpp)
target_compile_definitions(${PROJECT_NAME}_copager PRIVATE "-DCOPAGER")
target_link_libraries(${PROJECT_NAME}_copager common numa gtest pthread dl comanche-pmempaged allocator-copager)
target_link_libraries(${PROJECT_NAME}_copager   rt phoenix)
target_compile_features(${PROJECT_NAME}_copager PRIVATE cxx_range_for)


#use block-nvme
add_executable(${PROJECT_NAME}_copager_NVME ${PROJECT_NAME}.cpp)
target_compile_definitions(${PROJECT_NAME}_copager_NVME PRIVATE "-DCOPAGER")
target_link_libraries(${PROJECT_NAME}_copager_NVME common numa gtest pthread dl comanche-pmempaged allocator-copager-nvme)
target_link_libraries(${PROJECT_NAME}_copager_NVME   rt phoenix)
target_compile_features(${PROJECT_NAME}_copager_NVME PRIVATE cxx_range_for)

#if(LINK_WITH_GTEST)
#target_link_libraries(${PROJECT_NAME}  GTest::GTest GTest::Main)
#target_link_libraries(${PROJECT_NAME}_tbb   GTest::GTest GTest::Main)
#target_link_libraries(${PROJECT_NAME}_simple   GTest::GTest GTest::Main)
#target_link_libraries(${PROJECT_NAME}_copager   GTest::GTest GTest::Main)
#target_link_libraries(${PROJECT_NAME}_copager_NVME   GTest::GTest GTest::Main)
#endif(LINK_WITH_GTEST)


