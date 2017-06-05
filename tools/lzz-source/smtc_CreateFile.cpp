// smtc_CreateFile.cpp
//

#include "smtc_CreateFile.h"
// semantic
#include "smtc_File.h"
#define LZZ_INLINE inline
namespace smtc
{
  FilePtr createFile (util::String const & fullname, util::String const & name, util::String const & ext, bool has_hash_lines, bool smart_write)
  {
    return new File (fullname, name, ext, has_hash_lines, smart_write);
  }
}
#undef LZZ_INLINE
