// util_FilenameImplPtr.h
//

#ifndef LZZ_util_FilenameImplPtr_h
#define LZZ_util_FilenameImplPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace util
{
  class FilenameImpl;
}
namespace util
{
  typedef util::BPtr <FilenameImpl> FilenameImplPtr;
}
#undef LZZ_INLINE
#endif
