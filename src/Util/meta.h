#ifndef _META_H_
#define _META_H_

#include <type_traits>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <type_traits>
#include <numeric>
#include <algorithm>

namespace omniclid{

namespace {
  template<typename T, typename N> constexpr bool Convertible()
  {
      return std::is_convertible<T, N>::value;
  }

  template<typename T, typename N> constexpr bool Same()
  {
      return std::is_same<T, N>::value;
  }


  template<bool B, class T = void>
  struct disable_if {};

  template<class T>
  struct disable_if<false, T> { typedef T type; };

  template<bool B, typename T = void>
  using Enable_if = typename std::enable_if<B,T>::type;
  template<bool B, typename T = void>
  using Disable_if = typename disable_if<B,T>::type;

  template<typename... T>
  using Common_type = typename std::common_type<T...>::type;

  template<typename C>
  using Value_type = typename C::value_type;

  typedef struct row_pointer{} row_pointer;
  typedef struct smart_pointr{} smart_pointer;
}


}
#endif
