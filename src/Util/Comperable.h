#ifndef _COMPERABLE_H_
#define _COMPERABLE_H_

namespace omniclid{

template <class T>
class less_than_comperable
{
public:
  friend bool operator>(const T& lhs, const T& rhs)
  {
    return rhs.operator<(lhs);
  }

  friend bool operator<=(const T& lhs, const T& rhs)
  {
    return !rhs.operator<(lhs);
  }

  friend bool operator>=(const T& lhs, const T& rhs)
  {
    return !lhs.operator<(rhs);
  }
};

template <class T>
class equal_comperable
{
public:
  friend bool operator!=(const T& lhs, const T& rhs)
  {
    return !lhs.operator == (rhs);
  }

};


template <class T>
class eq_leth_comperable : public equal_comperable<T> , public less_than_comperable<T>
{

};
}
#endif
