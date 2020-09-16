cmake_minimum_required(VERSION 3.15)
project(ooop_nsu)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(word_count lab00b/main.cpp)
add_executable(ooop_lab01 lab01/main.cpp lab01/Tritset.cpp lab01/Tritset.h lab01/tests.cpp)

target_link_libraries(ooop_lab01 gtest gtest_main)