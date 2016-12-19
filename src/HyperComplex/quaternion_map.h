#ifndef _QUATERNION_MAP_H_
#define _QUATERNION_MAP_H_

#include "hypercomplex_map.h"
#include <boost/preprocessor.hpp>


namespace omniclid{

struct quaternion_map : public hypercomplex_map<4>{
public:

/*
  using opmap =  meta_map <0,
    kv< x<1,1> ,1>, kv< x<1,2> , 2>, kv< x<1,3> , 3>, kv< x<1,4>, 4>,
    kv< x<2,1> ,2>, kv< x<2,2> ,-1>, kv< x<2,3> , 4>, kv< x<2,4>,-3>,
    kv< x<3,1> ,3>, kv< x<3,2> ,-4>, kv< x<3,3> ,-1>, kv< x<3,4>, 2>,
    kv< x<4,1> ,4>, kv< x<4,2> , 3>, kv< x<4,3> ,-2>, kv< x<4,4>,-1>
  >;
*/


  using opmap = meta_list<0,
                          1, 2, 3, 4,
                          2,-1, 4,-3,
                          3,-4,-1, 2,
                          4, 3,-2,-1
                          >;

  CREATE(16,quaternion_map)

};

}

#endif
