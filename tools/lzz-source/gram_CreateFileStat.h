// gram_CreateFileStat.h
//

#ifndef LZZ_gram_CreateFileStat_h
#define LZZ_gram_CreateFileStat_h
// gram
#include "gram_FileStatPtr.h"

// util
#include "util_Filename.h"
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  FileStatPtr createFileStat (util::Filename const & filename, bool insert);
}
namespace gram
{
  FileStatPtr createFileStat (util::String const & str, util::Loc const & loc, bool insert);
}
#undef LZZ_INLINE
#endif
