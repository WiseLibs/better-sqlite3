// util_GetTempDir.cpp
//

#include "util_GetTempDir.h"
// std lib
#include <unistd.h>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define LZZ_INLINE inline
namespace util
{
  bool getTempDir (char const * prefix, util::String & dir)
  {
    enum { MAXLEN = 128 };
    assert (strlen (prefix) < MAXLEN - 7);
    char filename [MAXLEN];
    sprintf (filename, "%sXXXXXX", prefix);

    bool result = false;
    if (mkdtemp (filename) != NULL)
    {
      dir = filename;
      result = true;
    }
    return result;
  }
}
#undef LZZ_INLINE
