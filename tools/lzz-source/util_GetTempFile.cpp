// util_GetTempFile.cpp
//

#include "util_GetTempFile.h"
// std lib
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

#if __GNUC__ < 3 || defined WIN32
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif
#define LZZ_INLINE inline
namespace util
{
  bool getTempFile (char const * prefix, util::String & temp_filename)
  {
    enum { MAXLEN = 64 };
    assert (strlen (prefix) < MAXLEN - 7);
    char filename [MAXLEN];
    sprintf (filename, "%sXXXXXX", prefix);

    // gcc 2.95 doesn't support mkstemp ... so do it manually
#if __GNUC__ < 3 || defined WIN32
    if (mktemp (filename) == NULL)
    {
      return false;
    }
    int fd = open (filename, O_RDWR|O_CREAT|O_EXCL, 0666);
#else
    int fd = mkstemp (filename);
#endif
    if (fd == -1)
    {
      return false;
    }
    close (fd);
    temp_filename = filename;
    return true;
  }
}
#undef LZZ_INLINE
