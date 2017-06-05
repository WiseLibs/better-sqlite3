// gram_FindIncludeFile.h
//

#ifndef LZZ_gram_FindIncludeFile_h
#define LZZ_gram_FindIncludeFile_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  bool findIncludeFile (util::String const & inclname, util::String const & name, bool sys, util::String & fullname);
}
#undef LZZ_INLINE
#endif
