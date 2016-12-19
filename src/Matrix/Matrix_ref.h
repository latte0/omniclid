#ifndef _MATRIX_REF_H_
#define _MATRIX_REF_H_

#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <numeric>
#include <algorithm>
#include <memory>

#include "Matrix_base.h"

namespace omniclid {

template<size_t N>
class Matrix_slice;

template<typename T, size_t N>
class Matrix;

template <typename T, size_t N>
class Matrix_ref : public Matrix_base<T,N> {
public:
  friend class Matrix<T,N>;
  //template<typename M> friend Enable_if<Matrix_type<M>(), ostream&> operator<<(ostream& os,  const M& m);


  using value_type = T;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  Matrix_ref() = default;
  Matrix_ref(Matrix_ref&&) = default;
  Matrix_ref& operator=(Matrix_ref&&) = default;
  Matrix_ref(const Matrix_ref&) = default;
  Matrix_ref& operator=(const Matrix_ref&) = default;
  ~Matrix_ref() = default;

  Matrix_ref(const Matrix_slice<N>& s, T* p, size_t size, std::vector<T>& v )
    : desc{s},
      start(p),
      finish( p + size )
     {
       elems = &v;
     }
  Matrix_ref(const Matrix_slice<N>& s, T* p) : desc{s}, start(p) {}

  iterator begin(){ return elems->begin(); }
  const_iterator begin() const { return elems->begin(); }
  iterator end(){ return elems->end(); }
  const_iterator end() const { return elems->end(); }


  size_t extent(size_t n) const { return desc.extents[n]; }
  size_t size() const { return elems->size(); }
  const Matrix_slice<N>& descriptor() const { return desc; }

  T* data() { return elems->data(); }
  const T* data() const { return elems->data(); }

  const size_t rows() const {
    return desc.extents[0];
  }

  Matrix_ref<T,N-1> row(size_t n){
    return Row<N>::impl(*this/*std::enable_shared_from_this<Matrix<T,N>>::shared_from_this()*/, n);
/*
      assert(n<rows());
      Matrix_slice<N-1> row;
      Matrix_impl::slice_dim<0>(n,desc,row);
      return {row,data(),size(),elems};
      */
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



  template<size_t NN,class = void>
  class Row{
  public:
    static Matrix_ref<T,NN-1> impl(Matrix_ref<T,N> &parent, size_t n ){
      assert(n<parent.rows());
      Matrix_slice<N-1> row;
      Matrix_impl::slice_dim<0>(n,parent.desc,row);
      return {row,parent.data(),parent.size(),parent.elems};
    }
  };

  template<class V>
  class Row<1, V>{
  public:
    static Matrix_ref<T,0> impl(Matrix_ref<T,N> &parent,size_t n){
  //    std::cout << "0matrixref:" << *(parent.data() +n)  << std::endl;
      return *(parent.data() +n);
    }
  };

  template<size_t NN ,class V> friend class Row;


private:
  Matrix_slice<N> desc;

  T* start;
  T* finish;
  std::vector<T>* elems;
};




template<typename T>
class Matrix_ref<T,0> : public Matrix_base<T,0> {
public:
  static constexpr size_t order = 0;
  using value_type = T;

  friend class Matrix<T,0>;
//  template<typename M> friend Enable_if<Matrix_type<M>(), ostream&> operator<<(ostream& os,  const M& m);


  Matrix_ref(T& x) : elem() {
    //std::cout << "this constructor is called" << std::endl;
    elem = &x;
  }
  Matrix_ref& operator=( T& value)
  {
    elem = &value;
    return *this;
  }

  T* begin(){ return elem; }
  const T* begin() const { return elem; }
  T* end(){ return (elem+1); }
  const T* end() const { return elem+1; }


  const size_t rows() const {
    return 0;
  }

  T& operator()(){return *elem;}
  const T& operator()() const { return *elem; }

  operator T&() { return *elem; }
  operator const T&() { return *elem; }

private:
  T* elem;
};

}

#endif
