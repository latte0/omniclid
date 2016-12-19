#ifndef _MATRIX_META_H_
#define _MATRIX_META_H_

#include <type_traits>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <type_traits>
#include <numeric>
#include <algorithm>

namespace omniclid{

template <typename T, size_t N>
class Matrix;
template <typename T, size_t N>
class Matrix_ref;

namespace {
  template <class T>
  struct is_matrix_type {
    static const bool value = false;
  };

  template <>
  template <typename T, size_t N>
  struct is_matrix_type<Matrix_ref<T,N>>{
    static const bool value = true;
  };

  template <>
  template <typename T, size_t N>
  struct is_matrix_type<Matrix<T,N>>{
    static const bool value = true;
  };

  template<typename M> constexpr bool Matrix_type()
  {
      return is_matrix_type<
              typename std::remove_pointer
              <
                  typename std::remove_reference
                  <
                    typename std::remove_cv<M>::type
                  >::type
              >::type
            >::value;
  }
}
}

#endif
