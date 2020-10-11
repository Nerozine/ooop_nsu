project(ooop_lab01_tests)

# adding the Google_Tests_run target
add_executable(ooop_lab01_tests tests.cpp ../Tritset.h ../Tritset.cpp ../trit.h ../trit.cpp)
target_link_libraries(ooop_lab01_tests gtest_main)