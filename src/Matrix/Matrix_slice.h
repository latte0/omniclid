#ifndef _MATRIX_SLICE_H_
#define _MATRIX_SLICE_H_

#include <iostream>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <numeric>
#include <algorithm>

#include "../Util/meta.h"
#include "Matrix_impl.h"

using namespace std;

namespace omniclid{

struct slice {
public:
  slice() :start(-1), length(-1), stride(1) {}
  explicit slice(size_t s) :start(s), length(-1), stride(1) {}
  slice(size_t s, size_t l, size_t n = 1) :start(s), length(l), stride(n) {}

  size_t operator()(size_t i) const { return start+i*stride; }

  //static slice all;

  size_t start;
  size_t length;
  size_t stride;
};

template<size_t N>
struct Matrix_slice{
public:
  Matrix_slice() = default;
  Matrix_slice(Matrix_slice&&) = default;
  Matrix_slice& operator=(Matrix_slice&&) = default;
  Matrix_slice(const Matrix_slice&) = default;
  Matrix_slice& operator=(const Matrix_slice&) = default;
  ~Matrix_slice() = default;

  Matrix_slice(size_t offset,
                initializer_list<size_t> exts)
  {
    	static_assert(exts.size()==N, "Matrix_slice_slice<N>:: ext mismatch");

      this->start = offset;
      this->extents = std::move(exts);
      Matrix_impl::compute_strides(this);
  }

  Matrix_slice(size_t offset,
                initializer_list<size_t> exts, initializer_list<size_t> strs)
  {
  	static_assert(exts.size()==N, "Matrix_slice<N>:: ext mismatch");
  	static_assert(strs.size()==N, "Matrix_slice<N>:: str mismatch");

    this->start = offset;
    this->extents = std::move(exts);
    this->strides = std::move(strs);
  }


  template<typename... Dims>
  Matrix_slice(Dims... dims)
  {
    this->start = 0;
    array<size_t,N> args { size_t(dims)... };
    this->extents = std::move(args);
    Matrix_impl::compute_strides<N>(*this);

  }

  template<typename... Dims,
            typename = Enable_if<Matrix_impl::All(Convertible<Dims,size_t>()...)>>
  size_t operator()(Dims... dims) const
  {
    	static_assert(sizeof...(Dims)==N, "Matrix_slice<N>::operator(): dimension mismatch");

      size_t args[N] { size_t(dims)... };

      return start+inner_product(args,args+N,strides.begin(), size_t{0});
  }

public:
  size_t size = 0;
  size_t start = 0;
  array<size_t,N> extents;
  array<size_t,N> strides;
};

template <>
struct Matrix_slice<0> {
  size_t operator()() const
  {
    return 0;
  }
};

/*

template<>
struct Matrix_slice<1> {
  size_t operator()(size_t i) const
  {
    return i;
  }
};


template<>
struct Matrix_slice<2>{
  size_t operator()(size_t i, size_t j) const
  {
    return start + i*strides[0] + j;
  }
};
*/
}
#endif
