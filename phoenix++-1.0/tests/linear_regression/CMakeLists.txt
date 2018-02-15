#add_definitions("-DMUST_REDUCE")
add_executable(linear_regression linear_regression.cpp)
target_link_libraries(linear_regression rt phoenix)

add_executable(linear_regression_tbb linear_regression.cpp)
target_link_libraries(linear_regression_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(linear_regression_tbb PRIVATE "-DTBB")

add_executable(linear_regression_simple linear_regression.cpp)
target_link_libraries(linear_regression_simple rt phoenix)
target_compile_definitions(linear_regression_simple PRIVATE "-DSIMPLE")

add_executable(linear_regression_copager linear_regression.cpp)
target_link_libraries(linear_regression_copager rt phoenix)
target_compile_definitions(linear_regression_copager PRIVATE "-DCOPAGER")


