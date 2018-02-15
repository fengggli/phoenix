#add_definitions("-DMUST_REDUCE")
add_executable(histogram histogram.cpp)
target_link_libraries(histogram rt phoenix)

add_executable(histogram_tbb histogram.cpp)
target_link_libraries(histogram_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(histogram_tbb PRIVATE "-DTBB")

add_executable(histogram_simple histogram.cpp)
target_link_libraries(histogram_simple rt phoenix)
target_compile_definitions(histogram_simple PRIVATE "-DSIMPLE")

add_executable(histogram_copager histogram.cpp)
target_link_libraries(histogram_copager rt phoenix)
target_compile_definitions(histogram_copager PRIVATE "-DCOPAGER")


