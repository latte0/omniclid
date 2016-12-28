cmake_minimum_required(VERSION 2.8)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()
set(GTEST_ROOT /usr/local/include/gtest)
include_directories(
  ${GTEST_ROOT}/include
  ../
)
add_executable(matrix_test matrix_test.cpp
)
target_link_libraries(matrix_test
  /usr/local/lib/libgtest.a
  /usr/local/lib/libgtest_main.a
  pthread
)
