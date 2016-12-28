#ifndef _MATRIX_H_
#define _MATRIX_H_


#include <iostream>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <type_traits>
#include <numeric>
#include <algorithm>
#include <memory>

#include "Matrix_base.h"
#include "Matrix_ref.h"
#include "../Util/meta.h"

namespace omniclid{

template<typename T, size_t N>
class Matrix_ref;




template <typename T, size_t N>
class Matrix : public Matrix_base<T,N> ,public std::enable_shared_from_this<Matrix<T,N>> {
public:

  friend class Matrix_ref<T,N>;

//  template<typename M> friend Enable_if<Matrix_type<M>(), ostream&> operator<<(ostream& os,  const M& m);


  Matrix() = default;
  Matrix(Matrix&&) = default;
  Matrix& operator=(Matrix&&) = default;
  Matrix(const Matrix&) = default;
  Matrix& operator=(const Matrix&) = default;
  ~Matrix() = default;


  using value_type = T;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;


  iterator begin(){ return elems.begin(); }
  const_iterator begin() const { return elems.begin(); }
  iterator end(){ return elems.end(); }
  const_iterator end() const { return elems.end(); }


  template<typename U>
  Matrix(const Matrix_ref<U,N>& x) {
    static_assert(Convertible<U,T>(), "Matrix constructor: incompatible element types");
    desc = x.desc;
    elems.assign(x.begin(), x.end());
  }

  template<typename U>
  Matrix& operator=(const Matrix_ref<U,N>& x)
  {
    static_assert(Convertible<U,T>(), "Matrix =: incompatible element types");

    desc = x.desc;
    elems.assign(x.begin(), x.end());
    return *this;
  }


  template<typename... Exts>
  explicit Matrix(Exts... exts): desc{exts...}, elems(desc.size)
  {
  }

  Matrix(Matrix_initializer<T,N> init){

    desc.extents = Matrix_impl::derive_extents<N>(init);

    Matrix_impl::compute_strides<N>(desc);
    elems.reserve(desc.size);
    Matrix_impl::insert_flat<N>(init, elems);
    assert(elems.size() == desc.size);
  }

  Matrix& operator=(Matrix_initializer<T,N> init)
  {
    elems.clear();
    elems.shrink_to_fit();

    desc.extents = Matrix_impl::derive_extents<N>(init);

    Matrix_impl::compute_strides<N>(desc);
    elems.reserve(desc.size);
    Matrix_impl::insert_flat<N>(init, elems);
    assert(elems.size() == desc.size);

    return *this;
  }

  template<typename U>
  Matrix(initializer_list<U>) = delete;
  template<typename U>
  Matrix &operator=(initializer_list<U>) = delete;

  template<typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), T&>
  operator()(Args... args)
  {
    assert(Matrix_impl::check_bounds<N>(desc, args...));
    return *(data() + desc(args...));
  }

  template<typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), const T&>
  operator()(Args... args) const
  {
    assert(Matrix_impl::check_bounds<N>(desc, args...));
    return *(data() + desc(args...));
  }


  template<typename... Args>
  Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T,N>>
  operator()(const Args&... args){
    Matrix_slice<N> d;
    d.start = Matrix_impl::do_slice(desc,d,args...);
    return {d, data()};
  }
  template<typename... Args>
  Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T,N>>
  operator()(const Args&... args) const{
    Matrix_slice<N> d;
    d.start = Matrix_impl::do_slice(desc,d,args...);
    return {d, data()};
  }

  Matrix_ref<T,N-1> operator[](size_t i) { return row(i); }
  Matrix_ref<const T, N-1> operator[](size_t i) const { return row(i); }

  size_t rows() const {
    return desc.extents[0];
  }


  size_t cols(typename std::enable_if<(N>=1),void>::type* t = nullptr) const{
    if(N==1) return 1;
    return desc.extents[N-2];
  }

  Matrix_ref<T,N-1> row(size_t n ){
    return Row<N>::impl(*this/*std::enable_shared_from_this<Matrix<T,N>>::shared_from_this()*/, n);
  }

  Matrix_ref<const T, N-1> row(size_t n) const{
    return Row<N>::impl(*this/*std::enable_shared_from_this<Matrix<T,N>>::shared_from_this()*/, n);

    /*
    assert(n<rows());
    Matrix_slice<N-1> row;
    Matrix_impl::slice_dim<0>(n,desc,row);
    return {row,data(),size(),elems};
    */
  }

  Matrix_ref<T, N-1> col(size_t n){
    assert(n<cols());
    Matrix_slice<N-1> col;
    Matrix_impl::slice_dim<1>(n,desc,col);
    return {col,data(),size(),elems};
  }
  Matrix_ref<const T,N-1> col(size_t n) const{
    assert(n<cols());
    Matrix_slice<N-1> col;
    Matrix_impl::slice_dim<1>(n,desc,col);
    return {col,data(),size(),elems};
  }

  size_t extent(size_t n) const { return desc.extents[n]; }
  size_t size() const { return elems.size(); }
  const Matrix_slice<N>& descriptor() const { return desc; }

  T* data() { return elems.data(); }
  const T* data() const { return elems.data(); }

  template<typename F>
  Matrix<T,N>& apply(F f)
  {
    for(auto& x : elems) f(x);
    return *this;
  }

  Matrix<T,N>& operator+=(const T& val)
  {
    return apply([&](T& a){ a+= val; });
  }

  Matrix<T,N>& operator-=(const T& val)
  {
    return apply([&](T& a){ a-= val; });
  }

  template<typename M, typename F>
  Enable_if<Matrix_type<M>(), Matrix<T,N>&> apply(M& m, F f)
  {
    assert(Matrix_impl::same_extents(desc, m.descriptor()));
    auto i = begin();
    auto j = m.begin();
    for(; i!=end(); ++i, ++j)
      f(*i,*j);
    return *this;
  }

  template<typename M>
  Enable_if<Matrix_type<M>(),Matrix<T,N>&> operator+=(const M& m)
  {
    static_assert(M::order==N, "+=: mismatched Matrix dimensions");
    assert(Matrix_impl::same_extents(desc,m.descriptor()));

    return apply(m, [](T& a, const Value_type<M>& b){ a+=b; });
  }

  template<typename M>
  Enable_if<Matrix_type<M>(),Matrix<T,N>&> operator-=(const M& m)
  {
    static_assert(M::order==N, "+=: mismatched Matrix dimensions");
    assert(Matrix_impl::same_extents(desc,m.descriptor()));

    return apply(m, [](T& a, const Value_type<M>& b){ a-=b; });
  }



private:
  Matrix_slice<N> desc;
  vector<T> elems;


//Partial template specialization technique
  template<size_t NN,class = void>
  class Row{
  public:
    static Matrix_ref<T,NN-1> impl(Matrix<T,N> &parent, size_t n ){
      assert(n<parent.rows());
      Matrix_slice<N-1> row;
      Matrix_impl::slice_dim<0>(n,parent.desc,row);
      return {row,parent.data(),parent.size(),parent.elems};
    }
  };

  template<class V>
  class Row<1, V>{
  public:
    static Matrix_ref<T,0> impl(Matrix<T,N> &parent,size_t n){
  //    std::cout << "0matrixref:" << *(parent.data() +n)  << std::endl;
      return *(parent.data() +n);
    }
  };

  template<size_t NN ,class V> friend class Row;



};

namespace {

  template<typename T, size_t N>
  auto operator+(const Matrix<T,N>& a, const Matrix<T,N>& b)
  {
    Matrix<T,N> res = a;
    res+=b;
    return res;
  }

  template<typename T, typename T2, size_t N,
          typename RT = Matrix<Common_type<Value_type<T>, Value_type<T2>>,N>>
  Matrix<RT, N> operator+(const Matrix<T,N>& a, const Matrix<T2, N>& b)
  {
    Matrix<RT, N> res = a;
    res+=b;
    return res;
  }

  template<typename T, size_t N>
  Matrix<T,N> operator+(const Matrix_ref<T,N>& x, const T& n)
  {
    Matrix<T,N> res = x;
    res+=n;
    return res;
  }

  template<typename T, size_t N>
  auto operator-(const Matrix<T,N>& a, const Matrix<T,N>& b)
  {
    Matrix<T,N> res = a;
    res-=b;
    return res;
  }

  template<typename T, typename T2, size_t N,
          typename RT = Matrix<Common_type<Value_type<T>, Value_type<T2>>,N>>
  Matrix<RT, N> operator-(const Matrix<T,N>& a, const Matrix<T2, N>& b)
  {
    Matrix<RT, N> res = a;
    res-=b;
    return res;
  }

  template<typename T, size_t N>
  Matrix<T,N> operator-(const Matrix_ref<T,N>& x, const T& n)
  {
    Matrix<T,N> res = x;
    res-=n;
    return res;
  }

  template<typename T>
  Matrix<T, 2> operator*(const Matrix<T,1>& u, const Matrix<T,1>& v)
  {
    const size_t n = u.extent(0);
    const size_t m = v.extent(0);
    Matrix<T,2> res(n,m);
    for(size_t i = 0; i!=n; ++i)
      for(size_t j =0; j!=m; ++j)
        res(i,j) = u[i]*v[j];
    return res;
  }

  template<typename T>
  Matrix<T,1> operator*(const Matrix<T,2>& m, const Matrix<T,1>& v)
  {
    assert(m.extent(1) == v.extent(0));
    const size_t nr = m.extent(0);
    const size_t nc = m.extent(1);
    Matrix<T,1> res(nc);
    for(size_t i = 0; i!= nr; ++i)
      for(size_t j = 0; j!=nc; ++j)
        res(i) += m(i,j)*v(j);
    return res;
  }

  template<typename T>
  Matrix<T,2> operator*(const Matrix<T,2>& m1, const Matrix<T,2>& m2)
  {
    const size_t nr = m1.extent(0);
    const size_t nc = m1.extent(1);
    assert(nc==m2.extent(0));
    const size_t p = m2.extent(1);
    Matrix<T,2> res(nr,p);
    for(size_t i = 0; i!=nr; ++i)
      for(size_t j = 0; j!=p; ++j)
        for(size_t k = 0; k!=nc; ++k)
          res(i,j) += m1(i,k)*m2(k,j);
    return res;
  }



}

/*
template<typename T>
class Matrix<T,1> : public Matrix_base<T,1> {
public:
  static constexpr size_t order = 0;
  using value_type = T;

  Matrix() = default;
  Matrix(Matrix&&) = default;
  Matrix& operator=(Matrix&&) = default;
  Matrix(const Matrix&) = default;
  Matrix& operator=(const Matrix&) = default;
  ~Matrix() = default;


    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;


    iterator begin(){ return elems.begin(); }
    const_iterator begin() const { return elems.begin(); }
    iterator end(){ return elems.end(); }
    const_iterator end() const { return elems.end(); }

  Matrix& operator=(const T& value)
  {
    elem = value;
    return *this;
  }

  T& operator()(){return elem;}
  const T& operator()() const { return elem; }

  operator T&() { return elem; }
  operator const T&() { return elem; }

private:
  Matrix_slice<N> desc;
  vector<T> elems;
};

*/

template<typename T>
class Matrix<T,0> : public Matrix_base<T,0>  {
public:
  static constexpr size_t order = 0;
  using value_type = T;

//  template<typename M> friend Enable_if<Matrix_type<M>(), ostream&> operator<<(ostream& os,  const M& m);


  Matrix(const T& x) : elem(x) {}
  Matrix& operator=(const T& value)
  {
    elem = value;
    return *this;
  }

  template<typename U>
  Matrix(const Matrix_ref<U,0>& x) {
    static_assert(Convertible<U,T>(), "Matrix constructor: incompatible element types");
    elem = static_cast<T>(*x.elem);
  }

  template<typename U>
  Matrix& operator=(const Matrix_ref<U,0>& x)
  {
    static_assert(Convertible<U,T>(), "Matrix =: incompatible element types");
    elem = static_cast<T>(*x.elem);
    return *this;
  }

  size_t rows() const {
    return 0;
  }

  T* begin(){ return &elem; }
  const T* begin() const { return &elem; }
  T* end(){ return &elem; }
  const T* end() const { return &elem; }

  T& operator()(){return elem;}
  const T& operator()() const { return elem; }

  operator T&() { return elem; }
  operator const T&() { return elem; }

private:
  T elem;
};

}
#endif
