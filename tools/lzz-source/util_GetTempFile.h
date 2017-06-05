// util_GetTempFile.h
//

#ifndef LZZ_util_GetTempFile_h
#define LZZ_util_GetTempFile_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  bool getTempFile (char const * prefix, util::String & temp_filename);
}
#undef LZZ_INLINE
#endif
