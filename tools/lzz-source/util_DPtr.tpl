// util_DPtr.tpl
//

#include "util_DPtr.h"
namespace util
{
  template <typename S, typename T>
  DPtr <S, T>::DPtr ()
    : BPtr <T> ()
    {}
}
namespace util
{
  template <typename S, typename T>
  DPtr <S, T>::DPtr (S * s)
    : BPtr <T> (s)
    {}
}
namespace util
{
  template <typename S, typename T>
  DPtr <S, T>::DPtr (BPtr <T> const & bptr)
    : BPtr <T> (bptr)
    {}
}
namespace util
{
  template <typename S, typename T>
  DPtr <S, T>::~ DPtr ()
    {}
}
namespace util
{
  template <typename S, typename T>
  DPtr <S, T> & DPtr <S, T>::operator = (BPtr <T> const & bptr)
    {
      BPtr <T>::operator = (bptr);
      return * this;
    }
}
