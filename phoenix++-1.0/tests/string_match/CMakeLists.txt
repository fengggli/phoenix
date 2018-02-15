#add_definitions("-DMUST_REDUCE")
add_executable(string_match string_match.cpp)
target_link_libraries(string_match rt phoenix)

add_executable(string_match_tbb string_match.cpp)
target_link_libraries(string_match_tbb ${TBB_LIBRARY} rt phoenix)
target_compile_definitions(string_match_tbb PRIVATE "-DTBB")

add_executable(string_match_simple string_match.cpp)
target_link_libraries(string_match_simple rt phoenix)
target_compile_definitions(string_match_simple PRIVATE "-DSIMPLE")

add_executable(string_match_copager string_match.cpp)
target_link_libraries(string_match_copager rt phoenix)
target_compile_definitions(string_match_copager PRIVATE "-DCOPAGER")


