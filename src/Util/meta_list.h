#ifndef _META_LIST_
#define _META_LIST_

namespace omniclid {
namespace {

  template <int err,int...>
  struct meta_list;

  template<bool flag, int err, int index, int value, int...>
  struct check_list;


  template <int err, int index, int value, int... rest>
  struct check_list<false, err, index, value ,rest...>
  {
    static constexpr int val = meta_list<err, rest...>::template get<index-1>::val;
  };

  template <int err, int index, int value, int... rest>
  struct check_list<true,err, index, value, rest...>
  {
    static constexpr int val = value;
  };


  template <int err>
  struct meta_list<err>
  {
      template<int index>
      struct get
      {
          static constexpr int val = err;
      };
  };

  template <int err,int... rest>
  struct meta_list
  {
    template<int index>
    struct get
    {
      static constexpr int val = check_list<(bool)(index == 0),err, index, rest...>::val;
    };
  };

}
}
#endif
