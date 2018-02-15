#add_definitions("-DMUST_REDUCE")
add_executable(matrix_multiply matrix_multiply.cpp)
target_link_libraries(matrix_multiply rt phoenix)

add_executable(matrix_multiply_tbb matrix_multiply.cpp)
target_link_libraries(matrix_multiply_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(matrix_multiply_tbb PRIVATE "-DTBB")

add_executable(matrix_multiply_simple matrix_multiply.cpp)
target_link_libraries(matrix_multiply_simple rt phoenix)
target_compile_definitions(matrix_multiply_simple PRIVATE "-DSIMPLE")

add_executable(matrix_multiply_copager matrix_multiply.cpp)
target_link_libraries(matrix_multiply_copager rt phoenix)
target_compile_definitions(matrix_multiply_copager PRIVATE "-DCOPAGER")


