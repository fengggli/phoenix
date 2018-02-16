#add_definitions("-DMUST_REDUCE")
add_executable(word_count word_count.cpp)
target_link_libraries(word_count rt phoenix)

add_executable(word_count_tbb word_count.cpp)
target_link_libraries(word_count_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(word_count_tbb PRIVATE "-DTBB")

add_executable(word_count_simple word_count.cpp)
target_link_libraries(word_count_simple rt phoenix)
target_compile_definitions(word_count_simple PRIVATE "-DSIMPLE")

add_executable(word_count_copager word_count.cpp)
target_link_libraries(word_count_copager rt phoenix)
target_compile_definitions(word_count_copager PRIVATE "-DCOPAGER")


