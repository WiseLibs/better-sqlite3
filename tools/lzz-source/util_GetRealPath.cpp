// util_GetRealPath.cpp
//

#include "util_GetRealPath.h"
#include <cstdlib>
#include <climits>
#define LZZ_INLINE inline
namespace util
{
  bool getRealPath (util::String const & file, util::String & real_file)
  {
    bool result = false;
    char resolved_path [PATH_MAX];
#ifdef WIN32
    if (_fullpath (resolved_path, file.c_str (), PATH_MAX) == resolved_path)
#else
    if (realpath (file.c_str (), resolved_path) == resolved_path)
#endif
    {
      real_file = resolved_path;
      result = true;
    }
    return result;
  }
}
#undef LZZ_INLINE
