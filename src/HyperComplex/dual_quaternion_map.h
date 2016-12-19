#ifndef _DUAL_QUATERNION_MAP_H_
#define _DUALQUATERNION_MAP_H_

#include "hypercomplex_map.h"
#include <boost/preprocessor.hpp>

namespace omniclid{

struct dual_quaternion_map : public hypercomplex_map<8>{
public:


  using opmap = meta_list<0,
                          1, 2, 3, 4, 5, 6, 7, 8,
                          2,-1, 4,-3, 6,-5, 8,-7,
                          3,-4,-1, 2, 7,-8,-5, 6,
                          4, 3,-2,-1, 8, 7,-6,-5,
                          5, 6, 7, 8, 0, 0, 0, 0,
                          6,-5, 8,-7, 0, 0, 0, 0,
                          7,-8,-5, 6, 0, 0, 0, 0,
                          8, 7,-6,-5, 0, 0, 0, 0
                          >;

  CREATE(64,quaternion_map)

};

}
