#ifndef _MATRIX_IMPL_H_
#define _MATRIX_IMPL_H_

#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <type_traits>
#include <numeric>
#include <algorithm>

#include "Matrix_base.h"
#include "Matrix_meta.h"
#include "Matrix_impl_detail.h"

namespace omniclid{

template <typename T, size_t N>
class Matrix;
template <typename T, size_t N>
class Matrix_base;
template <typename T, size_t N>
class Matrix_ref;
template<size_t N>
class Matrix_slice;
class slice;

using namespace std;

namespace Matrix_impl
{
  template <std::size_t N, typename List>
    bool check_non_jagged(const List& list);


  template<std::size_t N, typename T, typename Vec>
  Enable_if<(N==1), void> add_list(const T* first, const T* last, Vec& vec)
  {
    vec.insert(vec.end(),first,last);
  }

  template<std::size_t N, typename T, typename Vec>
  Enable_if<(N>1), void> add_list(const initializer_list<T>* first, const initializer_list<T>* last, Vec& vec)
  {
    for (;first!=last;++first)
      add_list<N-1>(first->begin(), first->end(), vec);

  }

  constexpr bool All() { return true; }

  template<typename... Args>
  constexpr bool All(bool b, Args... args)
  {
    return b && All(args...);
  }

  template<std::size_t N, typename I, typename List>
    Enable_if<(N==1), void> add_extents(I& first, const List& list)
  {
    *first++ = list.size();
  }

  template<std::size_t N, typename I, typename List>
    Enable_if<(N>1), void> add_extents(I& first, const List& list)
  {
    assert(check_non_jagged<N>(list));
    *first++ = list.size();
    add_extents<N-1>(first, *list.begin());
  }



  template<std::size_t N, typename List>
    std::array<std::size_t, N> derive_extents(const List& list)
  {
    std::array<std::size_t, N> a;
    auto f = a.begin();
    add_extents<N>(f,list);
    return a;
  }

  template <std::size_t N, typename List>
    bool check_non_jagged(const List& list)
  {
    auto i = list.begin();
    for(auto j = i+1; j!=list.end(); ++j)
      if(derive_extents<N-1>(*i) != derive_extents<N-1>(*j))
        return false;
    return true;
  }

  template<int N>
    void compute_strides(Matrix_slice<N>& ms)
  {
    size_t st = 1;
    for(int i = N-1; i>=0; --i){
      ms.strides[i] = st;
      st *= ms.extents[i];
    }
    ms.size = st;
  }

  template<size_t N, typename... Dims>
    bool check_bounds(const Matrix_slice<N>& slice, Dims... dims)
  {
    size_t indexes[N] {size_t(dims)...};
    return equal(indexes, indexes+N, slice.extents.begin(), less<size_t> {});
  }

  template<size_t N, typename T, typename Vec>
    void insert_flat(initializer_list<T> list, Vec& vec)
  {
    add_list<N>(list.begin(), list.end(), vec);
  }

  template<typename... Args>
    constexpr bool Requesting_element()
  {
    return All(Convertible<Args,size_t>()... );
  }

  template<typename... Args>
    constexpr bool Requesting_slice()
  {
    return All(Same<Args,slice>()... );
  }

  template<typename T>
  T dot_product(const Matrix_ref<T,1>& a, const Matrix_ref<T,1>& b)
  {
    return inner_product(a.begin(), a.end(), b.begin(), 0.0);
  }

  template<typename T>
  T dot_product(const Matrix<T,1>& a, const Matrix<T,1>& b)
  {
    return inner_product(a.begin(), a.end(), b.begin(), 0.0);
  }


  template<size_t N, typename T>
  size_t do_slice_dim(const Matrix_slice<N>& os, Matrix_slice<N>& ns, const T& s)
  {
    return 0;
  }


  template<size_t N>
  size_t do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns)
  {
    return 0;
  }

  template<size_t N, typename T, typename... Args>
  size_t do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns, const T& s, const Args&... args)
  {
    size_t m = do_slice_dim<sizeof...(Args)+1>(os,ns,s);
    size_t n = do_slice(os,ns,args...);
    return m+n;
  }

  template<size_t Dim, size_t N>
  size_t slice_dim(size_t n,const Matrix_slice<N>& desc, Matrix_slice<N-1>& row)
  { return detail::Slice_dim<Dim,N>::impl(n,desc,row); }

  template<size_t N>
  bool same_extents(const Matrix_slice<N>& desc1, const Matrix_slice<N>& desc2)
  {
      return ((desc1.start == desc2.start) && (desc1.size == desc2.size) && (desc1.extents == desc2.extents) && (desc1.strides == desc2.strides));
  }



};

}





#endif
