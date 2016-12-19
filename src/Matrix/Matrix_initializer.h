#ifndef _MATRIX_INITIALIZER_H_
#define _MATRIX_INITIALIZER_H_

#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <type_traits>
#include <numeric>
#include <algorithm>

using namespace std;

namespace omniclid{

template<typename T, size_t N>
struct Matrix_init {
  using type = initializer_list<typename Matrix_init<T, N-1>::type>;
};

template<typename T>
struct Matrix_init<T,1> {
  using type = initializer_list<T>;
};

template<typename T>
struct Matrix_init<T,0>;

template<typename T, size_t N>
using Matrix_initializer = typename Matrix_init<T, N>::type;

}

#endif
