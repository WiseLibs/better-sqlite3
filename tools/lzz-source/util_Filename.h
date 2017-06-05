// util_Filename.h
//

#ifndef LZZ_util_Filename_h
#define LZZ_util_Filename_h
// util
#include "util_FilenameImpl.h"
#define LZZ_INLINE inline
namespace util
{
  struct FilenameImpl;
}
namespace util
{
  class Filename
  {
    static FilenameImpl def_impl;
    FilenameImpl const * m_impl;
  public:
    Filename ();
    explicit Filename (FilenameImpl const * impl);
    bool isSet () const;
    char const * getName () const;
    char const * getRealName () const;
    FilenameImpl const * getImpl () const;
  };
}
namespace util
{
  bool operator == (Filename const & a, Filename const & b);
}
namespace util
{
  bool operator != (Filename const & a, Filename const & b);
}
namespace util
{
  bool operator < (Filename const & a, Filename const & b);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "util_Filename.inl"
#endif
#endif
