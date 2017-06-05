// util_BPtr.tpl
//

#include "util_BPtr.h"
// std lib
#include <cassert>
namespace util
{
  template <typename T>
  BPtr <T>::BPtr ()
    : m_t (0), m_num_ref (0)
    {}
}
namespace util
{
  template <typename T>
  BPtr <T>::BPtr (T * t)
    : m_t (t), m_num_ref (new int)
    {
      * m_num_ref = 1;
    }
}
namespace util
{
  template <typename T>
  BPtr <T>::~ BPtr ()
    {
      if (m_num_ref && -- * m_num_ref == 0)
      {
        delete m_num_ref;
        delete m_t;
      }
    }
}
namespace util
{
  template <typename T>
  BPtr <T> & BPtr <T>::operator = (BPtr <T> const & bptr)
    {
      if (bptr.m_num_ref)
      {
        ++ * bptr.m_num_ref;
      }
      if (m_num_ref && -- * m_num_ref == 0)
      {
        delete m_num_ref;
        delete m_t;
      }
      m_t = bptr.m_t;
      m_num_ref = bptr.m_num_ref;
      return * this;
    }
}
namespace util
{
  template <typename T>
  BPtr <T> BPtr <T>::unref () const
    {
      BPtr <T> bptr;
      bptr.m_t = m_t;
      return bptr;
    }
}
namespace util
{
  template <typename T>
  BPtr <T> BPtr <T>::unref (T * t)
    {
      BPtr <T> bptr;
      bptr.m_t = t;
      return bptr;
    }
}
