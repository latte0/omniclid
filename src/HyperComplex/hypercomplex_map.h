#ifndef _HYPERCOMPLEX_MAP_H_
#define _HYPERCOMPLEX_MAP_H_

#include <map>
#include <utility>
#include <type_traits>
#include <cmath>

#include "../Util/meta_list.h"
#include "../Util/meta_map.h"

namespace omniclid{

namespace{
  template <class Head, class Tale>
  constexpr Head mult_seq(const Head& head, const Tale& tale)
  {
    return head * tale;
  }
  template <class Head, class... Nums>
  constexpr Head mult_seq(const Head& head, const Nums&... nums)
  {
    return head * mult_seq(head, nums...);

  }
  template <class Head, class Tale>
  constexpr Head mult_seq(Head&& head, Tale&& tale)
  {
    return std::forward<Head>(head * tale);
  }
  template <class Head, class... Nums>
  constexpr Head mult_seq(Head&& head, Nums&&... nums)
  {
    return std::forward<Head>(std::forward<Head>(head) * mult_seq(std::forward<Head>(nums)...));
  }

  template <class T>
  constexpr T abs_t(const T& abs){
    return abs > 0 ? abs : -abs;
  }
  template <class T>
  constexpr T abs_t(T&& abs){
    return abs > 0 ? std::forward<T>(abs) : -std::forward<T>(abs);
  }

/*
  template <class Head, class... T1, class T2>
  constexpr auto
  Vec_seq<class... T2>(const T2& head, const T2&... t2) ->
  decltype( std::declval<T1>() * std::declval<T2>() );
  */
/*
  template <class vec1head, class vec1rest>
  struct meta_vec{
    static constexpr int N = 2;
    template <class vec2head, class vec2rest>
    struct multiply
    {
      static constexpr decltype( std::declval<vec1head>() * std::declval<vec2head>() )
      val = ;
    };
  };

  template <class vec1head, class... vec1rest>
  struct meta_vec{
    static constexpr int N = 1 + sizeof...(vec1rest);
    template <class vec2head, class... vec2rest>
    struct multiply
    {
      static_assert(N == sizeof...(vec2rest))
      static constexpr decltype( std::declval<vec1head>() * std::declval<vec2head>() )
      val = 1;
    };
  };
  */

  template<int... head2>
  struct meta_vec_multiplyer{};


  template<int head1, int... rest1>
  struct meta_vec_multiplyer<head1, rest1...>
  {

      template<int head2, int... rest2>
      struct get
      {
          static constexpr int val = head1 * head2 + meta_vec_multiplyer<rest1...>::template get<rest2...>::val;
      };

  };
      template<int head1>
      struct meta_vec_multiplyer<head1>
      {
          template<int head2>
          struct get
          {
              static constexpr int val = head1 * head2;
          };
      };

}

#define OPMAP_INS(z, n, d) dy_map->insert(std::map<int,int>::value_type( n ,static_cast<int>(opmap::template get< n >::val) ));\


#define  CREATE_MAP(nn) inline static auto *createdymap() { \
     auto* dy_map = new std::map<int, int>(); \
     BOOST_PP_REPEAT(nn, OPMAP_INS, _)\
     return dy_map ;\
  }\
  static auto get_dy_opmap(int i){\
    static std::map<int, int>* dy_opmap = createdymap();\
    return dy_opmap->find(i)->second;\
  }\


  namespace{
    template < typename T >
    constexpr T sqrt( T s )
    {
        T x = s / 2.0 ;
        T prev = 0.0 ;

        while ( x != prev )
        {
            prev = x ;
            x = (x + s / x ) / 2.0 ;
        }
        return x ;
    }

    template<int _A, int _B ,int NN, typename Multiply>
    static constexpr int divmap_comp_help();

  /*
    template<int I, int J>
    static constexpr int XX(){
      return meta_vec_multiplyer<4,1>::template get<I,J>::val;
    }

  */

    template<bool AS, int _A, int _B ,int NN,typename Multiply>
    struct divmap_comp_recursive_help;

    template<int _A, int _B ,int NN, typename Multiply>
    struct divmap_comp_recursive_help<true, _A, _B, NN, Multiply>{
      static constexpr int val = NN;
    };
    template< int _A, int _B ,int NN, typename Multiply>
    struct divmap_comp_recursive_help<false, _A, _B, NN, Multiply>{
      static constexpr int val = divmap_comp_help<_A,_B,NN+1, Multiply>();
    };

    template<int _A, int _B ,int NN, typename Multiply>
    static constexpr int divmap_comp_help(){ return divmap_comp_recursive_help< abs_t(Multiply::opmap::template get<Multiply::dim*NN + _B>::val ) -1 == _A, _A, _B, NN, Multiply>::val; }

    template<int _A, int _B ,typename Multiply>
      static constexpr int get_divmap_res(){
        constexpr int ret = divmap_comp_help<_A,_B,0,Multiply>();
        if(Multiply::opmap::template get<Multiply::dim*ret + _B>::val < 0) return -ret;
        return ret;
      }
  }

  #define LOOPKV(z,n,d)  get_divmap_res< n / dim , n % dim , d >(),

  #define META_DIVMAP_CREATE(NN, OPNAME) typedef meta_list<-1, \
      BOOST_PP_REPEAT(NN,LOOPKV, OPNAME )\
      -1> opdivmap;
// dummymap
  #define OPDIVMAP_INS(z, n, d) dy_divmap->insert(std::map<int,int>::value_type( n ,static_cast<int>(opdivmap::template get< n >::val) ));\


  #define  CREATE_DIVMAP(nn) inline static auto *createdydivmap() { \
           auto* dy_divmap = new std::map<int, int>(); \
           BOOST_PP_REPEAT(nn, OPDIVMAP_INS, _)\
           return dy_divmap ;\
        }\
        static auto get_dy_opdivmap(int i){\
          static std::map<int, int>* dy_opdivmap = createdymap();\
          return dy_opdivmap->find(i)->second;\
        }

  #define CREATE(NN, MAPNAME) CREATE_MAP(NN)\
    META_DIVMAP_CREATE(NN, MAPNAME)\
    CREATE_DIVMAP(NN)


template < size_t N>
struct hypercomplex_map{
  static constexpr size_t dim = N;

  using mvm = meta_vec_multiplyer<dim,1>;

  template<int I, int J>
  static constexpr int x = mvm::template get<I-1, J-1>::val;

};

}


#endif
