// util_DPtr.h
//

#ifndef LZZ_util_DPtr_h
#define LZZ_util_DPtr_h
// util
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace util
{
  template <typename S, typename T>
  class DPtr : public BPtr <T>
  {
  public:
    DPtr ();
    DPtr (S * s);
    DPtr (BPtr <T> const & bptr);
    ~ DPtr ();
    DPtr <S, T> & operator = (BPtr <T> const & bptr);
    S * operator -> () const;
    S & operator * () const;
  };
}
namespace util
{
  template <typename S, typename T>
  LZZ_INLINE S * DPtr <S, T>::operator -> () const
    {
      return static_cast <S *> (this->pointer ());
    }
}
namespace util
{
  template <typename S, typename T>
  LZZ_INLINE S & DPtr <S, T>::operator * () const
    {
      return * static_cast <S *> (this->pointer ());
    }
}
#undef LZZ_INLINE
#endif
