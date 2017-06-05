// util_GetEnv.cpp
//

#include "util_GetEnv.h"
// std lib
#include <cstdlib>
#define LZZ_INLINE inline
namespace util
{
  bool getEnv (char const * name, util::String & value)
  {
    bool result = false;
    const char * env_str = getenv (name);
    if (env_str)
    {
      value = env_str;
      result = true;
    }
    return result;
  }
}
namespace util
{
  util::String getEnv (char const * name)
  {
    util::String value;
    getEnv (name, value);
    return value;
  }
}
#undef LZZ_INLINE
