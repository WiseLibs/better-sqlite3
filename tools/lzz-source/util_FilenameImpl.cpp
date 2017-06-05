// util_FilenameImpl.cpp
//

#include "util_FilenameImpl.h"
#define LZZ_INLINE inline
namespace util
{
  FilenameImpl::FilenameImpl (char const * name, char const * realname)
    : name (name), realname (realname)
    {}
}
#undef LZZ_INLINE
