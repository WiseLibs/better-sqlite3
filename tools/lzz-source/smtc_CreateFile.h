// smtc_CreateFile.h
//

#ifndef LZZ_smtc_CreateFile_h
#define LZZ_smtc_CreateFile_h
// semantic
#include "smtc_FilePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  FilePtr createFile (util::String const & fullname, util::String const & name, util::String const & ext, bool has_hash_lines, bool smart_write);
}
#undef LZZ_INLINE
#endif
