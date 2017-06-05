// util_BPtr.h
//

#ifndef LZZ_util_BPtr_h
#define LZZ_util_BPtr_h
// std lib
#include <cassert>
#include <cstddef>
#define LZZ_INLINE inline
namespace util
{
  template <typename T>
  class BPtr
  {
    T * m_t;
    int * m_num_ref;
  public:
    BPtr ();
    BPtr (T * t);
    BPtr (BPtr <T> const & bptr);
    ~ BPtr ();
    BPtr <T> & operator = (BPtr <T> const & bptr);
    T * operator -> () const;
    T & operator * () const;
    bool isSet () const;
    T * pointer () const;
    size_t getHandle () const;
    BPtr <T> unref () const;
    static BPtr <T> unref (T * t);
  };
}
namespace util
{
  template <typename T>
  LZZ_INLINE BPtr <T>::BPtr (BPtr <T> const & bptr)
    : m_t (bptr.m_t), m_num_ref (bptr.m_num_ref)
    {
      if (m_num_ref)
      {
        ++ * m_num_ref;
      }
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE T * BPtr <T>::operator -> () const
    {
      assert (m_t != 0);
      return m_t;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE T & BPtr <T>::operator * () const
    {
      assert (m_t != 0);
      return * m_t;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool BPtr <T>::isSet () const
    {
      return m_t != 0;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE T * BPtr <T>::pointer () const
    {
      assert (m_t != 0);
      return m_t;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE size_t BPtr <T>::getHandle () const
    {
      return (size_t) m_t;
    }
}
#undef LZZ_INLINE
#endif
