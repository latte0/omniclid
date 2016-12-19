#ifndef _HYPERCOMPLEX_H_
#define _HYPERCOMPLEX_H_

#include <iostream>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <type_traits>

#include "../Util/Amount.h"
#include "../Util/meta_map.h"
#include "quaternion_map.h"

namespace omniclid{

struct HyperComplex_tagged{};
template <typename Multiply, typename R, typename Tag >
struct HyperComplex;

using intpair = std::pair<int,int>;

namespace{

  template<class T>
  constexpr typename std::enable_if<std::is_fundamental<T>::value , T>::type
  _abs(const T& value){ return (value > 0 ) ? value : -value; }


  template <  typename Multiply,
              typename R,
              typename Tag
          >
  std::ostream& operator<<(std::ostream& os, const HyperComplex< Multiply,R,Tag> &val);

}

template <typename Tag = HyperComplex_tagged>
struct HyperComplex_base{
  HyperComplex_base() = default;
  HyperComplex_base(HyperComplex_base const&) = default;
  HyperComplex_base(HyperComplex_base &&) = default;

  HyperComplex_base & operator=(HyperComplex_base const&) = default;
  HyperComplex_base & operator=(HyperComplex_base &&) = default;

};





template <size_t N,
          typename R = double,
          typename Tag = HyperComplex_tagged,
          typename Multiply = quaternion_map,
          typename std::enable_if<std::is_fundamental<R>::value>::type* = nullptr
          >
struct HyperComplex_unit : public HyperComplex_base<Tag>, protected Amount<R, Tag>{
public:

 static constexpr size_t dim = N;

 typedef HyperComplex_unit<N,R,Tag> type;

 typedef R value_type;
 typedef Tag tag_type;

 HyperComplex_unit() = default;
 HyperComplex_unit(HyperComplex_unit const&) = default;
 HyperComplex_unit(HyperComplex_unit &&) = default;

 HyperComplex_unit & operator=(HyperComplex_unit const&) = default;
 HyperComplex_unit & operator=(HyperComplex_unit &&) = default;

 HyperComplex_unit(R const& v)
   : Amount<R,Tag>(v) { }
 HyperComplex_unit(R && v)
   : Amount<R,Tag>(std::move(v)){}

   template <typename T , typename std::enable_if<std::is_fundamental<T>::value>::type* = nullptr>
   HyperComplex_unit(T const& val)
   : Amount<R, Tag>(static_cast<double>(val)){}

   template <typename T , typename std::enable_if<std::is_fundamental<T>::value>::type* = nullptr>
   HyperComplex_unit(T && val)
   : Amount<R, Tag>(std::move(static_cast<double>(val))){}

   using This = HyperComplex_unit<N,R,Tag>;

   const R get_value() const{  return Amount<R, Tag>::amount; }


   bool operator == (This const& v) const{  return Amount<R, Tag>::amount == v.value(); }
   bool operator!=(const This& v) { return !Amount<R, Tag>::amount == v.value(); }
   bool operator<(const This& v){  return Amount<R, Tag>::amount < v.value(); }
   bool operator<=(const This& v){  return Amount<R, Tag>::amount <= v.value(); }
   bool operator>(const This& v){  return Amount<R, Tag>::amount > v.value(); }
   bool operator>=(const This& v){  return Amount<R, Tag>::amount >= v.value(); }
/*
   template <typename T>
   typename std::enable_if<std::is_fundamental<T>::value, HyperComplex_unit&>::type operator+=(const T& val){
     Amount<R, Tag>::amount += val;
     return *this;
   }
   */
   HyperComplex_unit& operator+=(const This& val){
     Amount<R, Tag>::amount += val.get_value();
     return *this;
   }
   HyperComplex_unit& operator-=(const This& val){
     Amount<R, Tag>::amount -= val.get_value();
     return *this;
   }



   template <typename T , typename std::enable_if<std::is_fundamental<T>::value>::type* = nullptr>
   HyperComplex_unit<N,R,Tag>& operator*=(const T& val){
     Amount<R,Tag>::amount *= val;
     return *this;
   }

   template <typename T , typename std::enable_if<std::is_fundamental<T>::value>::type* = nullptr>
   HyperComplex_unit<N,R,Tag>& operator/=(const T& val){
     Amount<R,Tag>::amount /= val;
     return *this;
   }

   R& value(){
     return Amount<R,Tag>::amount;
   }

   const size_t get_dim() const{
     return dim;
   }

};

template < typename Multiply = quaternion_map, typename R = double, typename Tag = HyperComplex_tagged>
struct HyperComplex {
public:
	static constexpr size_t order = Multiply::dim;

  typedef R value_type;
  typedef Tag tag_type;

	using iterator = typename std::array<R,order>::iterator;
	using const_iterator = typename std::array<R,order>::const_iterator;
  using This = HyperComplex<Multiply,R,Tag>;

  std::array<R, order> hypercomplex;

	HyperComplex() = default;
	HyperComplex(const HyperComplex& val):hypercomplex(val.hypercomplex){}
	HyperComplex& operator=(const HyperComplex& val){
    hypercomplex = val.hypercompolex;
  };
	~HyperComplex() = default;

  HyperComplex(const std::initializer_list<R>  &list){
    assert(list.size() == order);
    auto i = 0;
    for(auto* it = list.begin(); it!= list.end() ; it++){
      hypercomplex.at(i) = *it;
      i++;
    }
  }
  HyperComplex(const R & val){
    hypercomplex[0] = val;
    auto size = hypercomplex.size();
    for(auto i = 1; i < size; i++){
      hypercomplex.at(i) = 0;
    }
  }
  HyperComplex& operator=(const std::initializer_list<R> &list){
    assert(list.size() == order);
    auto i = 0;
    for(auto* it = list.begin(); it!= list.end() ; it++){
      hypercomplex.at(i) = *it;
      i++;
    }
  }
  HyperComplex(std::initializer_list<R> &&list){
    assert(list.size() == order);
    auto i = 0;
    for(auto* it = list.begin(); it!= list.end() ; it++){
      hypercomplex.at(i) = *it;
      i++;
    }
  }
  template <  size_t Num1 >
  HyperComplex(const HyperComplex_unit<Num1, R, Tag>& val){
    for(auto i = 0; i < order ; i++){
      hypercomplex.at(i) = (Num1 == i) ? val.get_value() : 0;
    }
  }



  HyperComplex& operator=(std::initializer_list<R> &&list){
    assert(list.size() == order);
    auto i = 0;
    for(auto* it = list.begin(); it!= list.end() ; it++){
      hypercomplex.at(i) = *it;
      i++;
    }
  }

  void set(const R &dim, const R &val)
  {
    try{
      hypercomplex.at(dim) = val;
    } catch (std::out_of_range& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  void set(R && dim, R && val){
    try{
      hypercomplex.at(dim) = val;
    } catch (std::out_of_range& e) {
      std::cerr << e.what() << std::endl;
    }
  }

	const value_type
	get_value(size_t num) const {
      try{
        return hypercomplex[num];
      }catch(std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        return 0;
      }
    }

  const size_t
  get_dim() const{
    return order;
  }


	template <size_t num> constexpr decltype(auto)
	get() { return HyperComplex_unit<num,R,Tag>(hypercomplex[num]); }

  const This get_conjugate() const
  {
      This ret;
      for(auto i = 0; i < order ; i++){
        ret.set(i,i!=0?-hypercomplex.at(i):hypercomplex.at(i));
      }
      return ret;
  }

  template <typename F>
  HyperComplex& apply(F f)
  {
    for(auto& x : hypercomplex) f(x);
    return *this;
  }
  template <typename T>
  typename std::enable_if<std::is_fundamental<T>::value, HyperComplex&>::type operator+=(const T& val){
//    return apply([&](T& a) { a+= val; });
    return hypercomplex[0] += val;
  }
  template <size_t Num>
  HyperComplex& operator+=(const HyperComplex_unit<Num, R, Tag>& val){
    try{
      hypercomplex[Num] += val.get_value();
    } catch (std::out_of_range& e) {
      std::cerr << e.what() << std::endl;
    }
    return *this;
  }
  HyperComplex& operator+=(const This& val){
    assert(order == val.order);
    for(int i = 0; i < order; i++) hypercomplex.at(i) += val.hypercomplex.at(i);
    return *this;
  }

  template <size_t Num>
  HyperComplex& operator-=(const HyperComplex_unit<Num, R, Tag>& val){
    try{
      hypercomplex.at(Num) -= val.get_value();
    } catch(std::out_of_range& e){
      std::cerr << e.what() << std::endl;
    }
    return *this;
  }
  HyperComplex& operator-=(const This& val){
    assert(order == val.order);
    for(int i = 0; i < order; i++) hypercomplex.at(i) -= val.hypercomplex.at(i);
    return *this;
  }



  auto p_or_m(int x){
    return x > 0 ? 1 : -1;
  };

//  template<int I>
  //auto multiply_impl(const This& val, const This& res);
/*
  template<int I, class U = void>
  struct Multiply_impl_struct {
    static This res(This& val0, const This& val1, const This& res1){
    return res1.hypercomplex[_abs(quaternion_map::opmap::template get<I>::val) - 1]
    += val0.hypercomplex[I / 4]
    * val1.hypercomplex[I % 4]
    * p_or_m(quaternion_map::opmap::template get<I>::val)
    + Multiply_impl_struct<I-1>::res(val0, val1,res1);
  }
  };
  template<int I >
  struct Multiply_impl_struct<I, typename std::enable_if<I==0>::type >{
    static This res(This& val0,const This& val1, const This& res1){
      return res1.hypercomplex[_abs(quaternion_map::opmap::template get<0>::val) - 1] += val0.hypercomplex[0] * val1.hypercomplex[0] * p_or_m(quaternion_map::opmap::template get<0>::val);
    }
  };




  template<int I>
  auto multiply_impl(const This& val0, const This& val1, const This& res){
    return Multiply_impl_struct<I>::res(val0, val1, res);//res.hypercomplex[_abs(quaternion_map::opmap::template get<I>::val) - 1] += hypercomplex[I / 4] * val.hypercomplex[I % 4] * p_or_m(quaternion_map::opmap::template get<I>::val) + multiply_impl<I-1>(val,res);
  }
*/


  HyperComplex& operator*=(const This& val){
    assert(order == val.order);
    HyperComplex<Multiply, R,Tag> res;

  //  multiply_impl<16>(*this,val,res);

    res.hypercomplex.fill(0);
    auto p_or_m = [](int x){
      return x > 0 ? 1 : -1;
    };
    for(int i = 0 ; i < order ; i++){
      for(int j = 0; j < order ; j++){
        int ret = Multiply::get_dy_opmap(i * order + j);
        res.hypercomplex.at(_abs(ret) - 1) += hypercomplex.at(i) * val.hypercomplex.at(j) * p_or_m(ret);
      }
    }
    hypercomplex.swap(res.hypercomplex);

    return *this;
  }

  HyperComplex& operator/=(const This& val){
    assert(order == val.order);
    HyperComplex<Multiply,R,Tag> res;

    auto denominator = (val * val.get_conjugate()).get<0>().get_value();

    auto numerator = *this * val.get_conjugate();

    for(auto i = 0; i < order; i ++){
      numerator.hypercomplex.at(i) /= denominator;
    }


    hypercomplex.swap(numerator.hypercomplex);


    return *this;
  }

  friend std::ostream& operator<< < Multiply,R, Tag >(std::ostream& os, const HyperComplex<Multiply,R,Tag> &val);

};

namespace{
  template <size_t N, typename Multiply, typename T = double, typename Tag = HyperComplex_tagged>
  auto make_hypercomplex()
  {
      HyperComplex_unit<N, T, Tag, Multiply> ret;
      return ret;
  }
}


namespace {

  template <  size_t Num1,
              size_t Num2,
              typename R = double,
              typename Tag = HyperComplex_tagged,
              typename Multiply = quaternion_map,
              const int ret = Multiply::opmap::template get<Num1*Multiply::dim+Num2>::val
          >
  auto operator*(const HyperComplex_unit<Num1, R, Tag>& val1, const HyperComplex_unit<Num2, R, Tag>& val2)
//  -> HyperComplex_unit<size_t(abs(ret)-1),R,Tag>
  {
    HyperComplex_unit<size_t(_abs(ret)-1),R,Tag> retvalue(0);
    if(ret<0) retvalue.value() = -1;
    else retvalue.value() = 1;
    retvalue *= val1.get_value();
    retvalue *= val2.get_value();
    return retvalue;
  }

  template <  size_t Num1,
              size_t Num2,
              typename R = double,
              typename Tag = HyperComplex_tagged,
              typename Multiply = quaternion_map,
              const int ret = Multiply::opdivmap::template get<Num1*Multiply::dim+Num2>::val
          >
  auto operator/(const HyperComplex_unit<Num1, R, Tag>& val1, const HyperComplex_unit<Num2, R, Tag>& val2)
//  -> HyperComplex_unit<size_t(abs(ret)-1),R,Tag>
  {
    HyperComplex_unit<size_t(_abs(ret)-1),R,Tag> retvalue(0);
    if(ret<0) retvalue.value() = -1;
    else retvalue.value() = 1;
    retvalue *= val1.get_value();
    retvalue /= val2.get_value();
    return retvalue;
  }

  template <  size_t Num1,
              size_t Num2,
              typename R = double,
              typename Tag = HyperComplex_tagged,
              typename Multiply = quaternion_map
          >
  auto operator+(const HyperComplex_unit<Num1, R, Tag>& val1, const HyperComplex_unit<Num2, R, Tag>& val2)
//  -> HyperComplex_unit<size_t(abs(ret)-1),R,Tag>
  {
    HyperComplex<Multiply, R, Tag> retvalue(0);
    retvalue += val1;
    retvalue += val2;
    return retvalue;
  }

  template <  size_t Num1,
              size_t Num2,
              typename R = double,
              typename Tag = HyperComplex_tagged,
              typename Multiply = quaternion_map
          >
  auto operator-(const HyperComplex_unit<Num1, R, Tag>& val1, const HyperComplex_unit<Num2, R, Tag>& val2)
//  -> HyperComplex_unit<size_t(abs(ret)-1),R,Tag>
  {
    HyperComplex<Multiply, R, Tag> retvalue(0);
    retvalue += val1;
    retvalue -= val2;
    return retvalue;
  }

  template <  size_t Num,
              typename Multiply,
              typename R,
              typename Tag
          >
  auto operator+(const HyperComplex< Multiply, R, Tag>& val1, const HyperComplex<Multiply, R, Tag>& val2)
  {
    HyperComplex<Multiply, R,Tag> retvalue(val1);
    retvalue+= val2;
    return retvalue;
  }
  template <    typename Multiply,
                typename R,
                typename Tag
            >
    auto operator-(const HyperComplex<Multiply, R, Tag>& val1, const HyperComplex<Multiply, R, Tag>& val2)
    {
      HyperComplex<Multiply, R,Tag> retvalue(val1);
      retvalue-= val2;
      return retvalue;
    }

  template <               typename Multiply,
              typename R,
              typename Tag
          >
  auto operator*(const HyperComplex<Multiply, R, Tag>& val1, const HyperComplex<Multiply, R, Tag>& val2)
  {
    HyperComplex<Multiply, R,Tag> retvalue(val1);
    retvalue*= val2;
    return retvalue;
  }

    template <  typename Multiply,
                typename R,
                typename Tag
            >
    auto operator/(const HyperComplex<Multiply, R, Tag>& val1, const HyperComplex<Multiply, R, Tag>& val2)
    {
      HyperComplex<Multiply, R,Tag> retvalue(val1);
      retvalue/= val2;
      return retvalue;
    }


    template <  typename Multiply,
                typename R,
                typename Tag
            >
    std::ostream& operator<<(std::ostream& os, const HyperComplex<Multiply,R,Tag> &val)
    {

        for(auto i = 0; i < Multiply::dim; i++){
          os << val.get_value(i) << '/';
        }
        return os;
    }

}

}

#endif
