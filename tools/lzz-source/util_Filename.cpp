// util_Filename.cpp
//

#include "util_Filename.h"
#ifndef LZZ_ENABLE_INLINE
#include "util_Filename.inl"
#endif
#define LZZ_INLINE inline
namespace util
{
  FilenameImpl Filename::def_impl ("nofile", "nofile");
}
namespace util
{
  Filename::Filename (FilenameImpl const * impl)
    : m_impl (impl)
    {}
}
namespace util
{
  FilenameImpl const * Filename::getImpl () const
    {
      return m_impl;
    }
}
namespace util
{
  bool operator == (Filename const & a, Filename const & b)
  {
    return a.getImpl () == b.getImpl ();
  }
}
namespace util
{
  bool operator < (Filename const & a, Filename const & b)
  {
    return a.getImpl () <  b.getImpl ();
  }
}
#undef LZZ_INLINE
