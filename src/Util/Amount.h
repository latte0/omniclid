#ifndef _AMOUNT_H_
#define _AMOUNT_H_

#include <iostream>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <numeric>
#include <algorithm>
#include <ostream>
#include <type_traits>

#include "Comperable.h"

namespace omniclid {

/*
template <typename T>
using Comperable<T> = eq_leth_comperable<T>;
*/
template <typename T, typename Tag>
class Amount {
public:
  static_assert(std::is_pod<T>::value, "you have to use only old-plane-data types in Amount class ");

  typedef T Amount_type;
  typedef Tag tag_type;

protected:
  Amount_type amount;

public:
  Amount() = default;
  Amount(Amount const&) = default;
  Amount(Amount &&) = default;

  Amount & operator=(Amount const&) = default;
  Amount & operator=(Amount &&) = default;

  Amount(Amount_type const& v)
    : amount(v) { }

  Amount(Amount_type && v)
    : amount(std::move(v)) {}

    constexpr T const* Data() const noexcept
    {
      return &amount;
    }

    T* Data() noexcept
    {
      return &amount;
    }



    constexpr bool operator == (Amount const& v) const{  return amount == v.amount; }
    constexpr bool operator!=(const Amount& v) { return !amount == v.amount; }
    constexpr bool operator<(const Amount& v){  return amount < v.amount; }
    constexpr bool operator<=(const Amount& v){  return amount <= v.amount; }
    constexpr bool operator>(const Amount& v){  return amount > v.amount; }
    constexpr bool operator>=(const Amount& v){  return amount >= v.amount; }

};


namespace {
  template <typename T, class Tag, class...Arguments>
  Amount<T, Tag> MakeAmount(Arguments &&... arguments)
  {
      static_assert(std::is_pod<T>::value, "You can only use plain-old-data types");
      return Amount<T, Tag>(std::forward<T>(arguments)...);
  }

}


}
#endif
