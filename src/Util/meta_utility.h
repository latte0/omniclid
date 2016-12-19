#ifndef _META_UTILITY_H_
#define _META_UTILITY_H_

#define DEFINE_TYPE_NAMED_PARAM(param) \
  template <class T>
  struct param {
    typedef T type;
  };

  template <class>
  struct is_ ## param ## _policy {
    static const bool value = false;
  };

  template <class T>
  struct is_ ## param ## _<param<T>>{
    static const bool value = true;
  };

#define DEFINE_BOOL_NAMED_PARAM(param)
template<bool V>
struct param{
  static const bool value = V;
};

template <class>
struct is ## param ## _policy {
  static const bool value = false;
};

template <bool V>
struct is_ ## param ## _policy<param<V>>{
  static const bool value = true;
};



struct not_found{}

template <template <class> class Pred,
          class Head, class.. Tail>
struct find_if_impl {
  typedef typename
  std::conditional<
    Pred<Head>::value,
    Head,
    typename find_if_impl<Pred, Tail...>::type
  >::type
  type;
};

template <template<class> class Pred, class... List>
struct get_required_arg{
  typedef typename find_if<Pred, List...>::type type;
  static_assert(!std::is_same<type, not_found>::value, "required policy not found");
}

template<class Opt, template <class> class Pred, class... List>
struct get_optional_arg{
private:
  typedef typename find_if<Pred, List...>::type result;
public:
  typedef typename
  std::conditional<
    !std::is_same<result, not_found>::value,
    result,
    Opt
  >::type;
  type;
}


#endif
