#add_definitions("-DMUST_REDUCE")
add_executable(kmeans kmeans.cpp)
target_link_libraries(kmeans rt phoenix)

add_executable(kmeans_tbb kmeans.cpp)
target_link_libraries(kmeans_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(kmeans_tbb PRIVATE "-DTBB")

#add_executable(kmeans_m_alloc kmeans.cpp)
#target_link_libraries(kmeans_m_alloc rt phoenix)
#target_compile_definitions(kmeans_m_alloc PRIVATE "-DM_ALLOC")

add_executable(kmeans_simple kmeans.cpp)
target_link_libraries(kmeans_simple rt phoenix)
target_compile_definitions(kmeans_simple PRIVATE "-DSIMPLE")

