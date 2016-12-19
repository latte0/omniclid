#ifndef _MATRIX_BASE_H_
#define _MATRIX_BASE_H_

#include <iostream>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <array>
#include <numeric>
#include <algorithm>
#include <ostream>

#include "../Util/meta.h"
#include "Matrix_meta.h"
#include "Matrix_slice.h"
#include "Matrix_impl.h"
#include "Matrix_initializer.h"

namespace omniclid{

template <typename T, size_t N >
class Matrix_base;

namespace{
  /*
  template<typename T, size_t NN, typename std::enable_if<(NN==0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix<T,NN>& m)
  template<typename T, size_t NN, typename std::enable_if<(NN==0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix_ref<T,NN>& m)
  template<typename T,size_t NN, typename std::enable_if<(NN>0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix_ref<T,NN>& m)
  template<typename T,size_t NN, typename std::enable_if<(NN>0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix<T,NN>& m)
  */
  template<typename M>
  Enable_if<Matrix_type<M>(),ostream&>
  operator<< (ostream& os, const M& m);
}

template<typename T, size_t N>
class Matrix_base {
public:

  static constexpr size_t order = N;

  Matrix_base() = default;

/*
  template<typename M>
  friend Enable_if<Matrix_type<M>(),ostream&>
    operator<< (ostream& os, const M& m);
*/


};

namespace {
/*
  template<typename T, size_t NN, typename std::enable_if<(NN==0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix<T,NN>& m)
  {
    os << m();
  }

  template<typename T, size_t NN, typename std::enable_if<(NN==0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix_ref<T,NN>& m)
  {
    os << m();
  }

  template<typename T,size_t NN, typename std::enable_if<(NN>0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix_ref<T,NN>& m)
  {
    os << '{';

    for (size_t i = 0; i!=m.rows(); ++i){
      os << m[i];
      if(i+1!=m.rows()) os << ',';
    }

    return os << '}';
  }

  template<typename T,size_t NN, typename std::enable_if<(NN>0),void>::type* v = nullptr>
  ostream& operator<<(ostream& os, const Matrix<T,NN>& m)
  {
    os << '{';
ambiguous overload for
    for (size_t i = 0; i!=m.rows(); ++i){
      os << m[i];
      if(i+1!=m.rows()) os << ',';
    }

    return os << '}';
  }
*/
}

namespace {
  template<typename M>
  Enable_if<Matrix_type<M>(),ostream&>
  operator<< (ostream& os, const M& m)
  {
    os << '{';
    auto i = 0;
    for(auto it = m.begin(); it != m.end(); it++){
      os<< *it << ' ';
      if(i == m.rows()){
        os <<','<< std::endl;
        i = 0;
      }else i++;

    }
    return os << '}' << std::endl;
  }
}


}

#endif
