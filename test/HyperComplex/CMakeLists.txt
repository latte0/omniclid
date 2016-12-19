cmake_minimum_required(VERSION 2.8)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
set(GTEST_ROOT /usr/local/include/gtest)
include_directories(
  ${GTEST_ROOT}/include
  ../
)
add_executable(hypercomplex_test hypercomplex_test.cpp
)
target_link_libraries(hypercomplex_test
  /usr/local/lib/libgtest.a
  /usr/local/lib/libgtest_main.a
  pthread
)
