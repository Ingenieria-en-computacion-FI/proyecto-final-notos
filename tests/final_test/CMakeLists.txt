set(NOTY_TEST_SUBDIR final_test)


message('\nGenerando: \"final test\":')


add_executable(final_test main.c)
target_link_libraries(final_test PRIVATE notOS)

set_testConfig(final_test)


