#ifndef _MATRIX_IMPL_DETAIL_H_
#define _MATRIX_IMPL_DETAIL_H_

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
class Matrix_base;
template <typename T, size_t N>
class Matrix_ref;
template<size_t N>
class Matrix_slice;
class slice;

namespace Matrix_impl{
  namespace detail
  {

    template<size_t Dim, size_t N>
    struct Slice_dim{
      static size_t impl(size_t n,const Matrix_slice<N>& desc, Matrix_slice<N-1>& row)
      { return 0; }
    };

    template<size_t N>
    struct Slice_dim<1,N>{
      static size_t impl(size_t n, const Matrix_slice<N>& desc, Matrix_slice<N-1>& row)
      {
        return 0;
      }
    };

    template<size_t N>
    struct Slice_dim<0,N>{
      static size_t impl(size_t n, const Matrix_slice<N>& desc, Matrix_slice<N-1>& row)
      {

    //    #include <iostream>

        std::array<size_t,N> ext = desc.extents;

    //    for(auto&& i : ext) std::cerr << i << std::endl;

        decltype(auto) pi_array = [](auto* it, auto* end){
          size_t value = 1;
          for(;it!=end;it++)  value *= *it;
          return value;
        };

        decltype(auto) get_array_point = [](int i,auto* it){
          for(int k = 0; k<i; k++ ) it++;
          return it;
        };

        row.size = desc.size;
        row.start = n * pi_array(get_array_point(1,ext.begin()), ext.end()) ;

        if(N==2){
            row.strides[0] = 1;
            row.extents[0] = *(ext.begin() + 1);
        }else{

          for(int i = 0; i< N-1; i++){
            if(i== int(N-2)) row.strides[i] = 1;
            else row.strides[i] = pi_array(get_array_point(2+i,ext.begin()), ext.end());


            row.extents[i] = ext[i+1];

        //    std::cerr << "loop" <<N << i<< row.strides[i] << row.extents[i] << std::endl;
          }
        }

        return 0;
      }
    };

  }

}

}

#endif
