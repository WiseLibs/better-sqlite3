// util_FilenameTable.h
//

#ifndef LZZ_util_FilenameTable_h
#define LZZ_util_FilenameTable_h
// util
#include "util_Filename.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  bool getFilename (util::String const & name, Filename & filename);
}
namespace util
{
  Filename storeFilename (util::String const & name);
}
#undef LZZ_INLINE
#endif
