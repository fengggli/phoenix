#add_definitions("-DMUST_REDUCE")
add_executable(kmeans kmeans.cpp)
target_link_libraries(kmeans rt phoenix)

add_executable(kmeans_tbb kmeans.cpp)
target_link_libraries(kmeans_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(kmeans_tbb PRIVATE "-DTBB")

add_executable(kmeans_simple kmeans.cpp)
target_link_libraries(kmeans_simple rt phoenix)
target_compile_definitions(kmeans_simple PRIVATE "-DSIMPLE")

add_executable(kmeans_copager kmeans.cpp)
target_compile_definitions(kmeans_copager PRIVATE "-DCOPAGER")
target_link_libraries(kmeans_copager common numa gtest pthread dl comanche-pmempaged)
target_link_libraries(kmeans_copager   rt phoenix)
target_compile_features(kmeans_copager PRIVATE cxx_range_for)

add_executable(kmeans_copager_NVME kmeans.cpp)
target_compile_definitions(kmeans_copager_NVME PRIVATE "-DCOPAGER -DUSE_SPDK_NVME_DEVICE")
target_link_libraries(kmeans_copager_NVME common numa gtest pthread dl comanche-pmempaged)
target_link_libraries(kmeans_copager_NVME   rt phoenix)
target_compile_features(kmeans_copager_NVME PRIVATE cxx_range_for)






