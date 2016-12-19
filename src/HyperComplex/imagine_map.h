#ifndef _IMAGINE_MAP_H_
#define _IMAGINE_MAP_H_

#include "hypercomplex_map.h"
#include <boost/preprocessor.hpp>

namespace omniclid{

struct imagine_map : public hypercomplex_map<2> {
public:

/*
  using opmap = meta_map< 0,
    kv< x<1,1>, 1> , kv< x<1,2> , 2>,
    kv< x<2,1>, 2> , kv< x<2,2> , -1>
  >;
*/

  using opmap = meta_list<0,
            1, 2,
            2,-1
  >;

  CREATE(4,imagine_map)

};

}
#endif
