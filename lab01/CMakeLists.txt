project(ooop_lab01)

add_executable(ooop_lab01 main.cpp Tritset.cpp Tritset.h trit.cpp trit.h)
add_subdirectory(tests)
target_link_libraries(ooop_lab01 gtest_main)