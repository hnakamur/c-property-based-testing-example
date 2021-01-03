enable_testing()

add_executable(round_up_test round_up_test.c)
target_link_libraries(round_up_test round)
add_test(NAME round_up_test COMMAND round_up_test)

add_executable(round_up_prop_test round_up_prop_test.c)
target_link_libraries(round_up_prop_test round libtheft m)
add_test(NAME round_up_prop_test COMMAND round_up_prop_test)
