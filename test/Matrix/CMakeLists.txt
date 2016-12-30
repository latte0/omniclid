cmake_minimum_required(VERSION 2.8)
add_executable(matrix_test matrix_test.cpp)
target_link_libraries(matrix_test
  gtest
  gtest_main
  pthread
)
