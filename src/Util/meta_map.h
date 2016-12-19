#ifndef _META_MAP_
#define _META_MAP_

namespace{

  template <int kk, int vv>
  struct kv
  {
      static constexpr int k = kk;
      static constexpr int v = vv;
  };

  template<bool flag, int err, int kk, int v, typename...>
  struct check;

  template <int err, typename...>
  struct meta_map;

  template <int err, int kk, int v, typename... rest>
  struct check<false,err, kk ,v,rest...>
  {
    static constexpr int val = meta_map<err, rest...>::template get<kk>::val;
  };

  template <int err,  int kk, int v, typename... rest>
  struct check<true,err, kk, v, rest...>
  {
    static constexpr int val = v;
  };



  template <int err>
  struct meta_map<err>
  {
      template<int>
      struct get
      {
          static constexpr int val = err;
      };
  };

  template<int err, int k, int v, typename... rest>
  struct meta_map<err, kv<k, v>, rest...>
  {
      template<int kk>
      struct get
      {
          static constexpr int val = check<(bool)(kk == k) ,err, kk, v,rest...>::val;

      };
  };
}

#endif
