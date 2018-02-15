#add_definitions("-DMUST_REDUCE")
add_executable(pca pca.cpp)
target_link_libraries(pca rt phoenix)

add_executable(pca_tbb pca.cpp)
target_link_libraries(pca_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(pca_tbb PRIVATE "-DTBB")

add_executable(pca_simple pca.cpp)
target_link_libraries(pca_simple rt phoenix)
target_compile_definitions(pca_simple PRIVATE "-DSIMPLE")

add_executable(pca_copager pca.cpp)
target_link_libraries(pca_copager rt phoenix)
target_compile_definitions(pca_copager PRIVATE "-DCOPAGER")


