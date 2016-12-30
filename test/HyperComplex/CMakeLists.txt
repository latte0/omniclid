cmake_minimum_required(VERSION 2.8)
add_executable(hypercomplex_test hypercomplex_test.cpp)
target_link_libraries(hypercomplex_test
  gtest
  gtest_main
  pthread
)
