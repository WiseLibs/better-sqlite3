// smtc_CreateDirectInit.h
//

#ifndef LZZ_smtc_CreateDirectInit_h
#define LZZ_smtc_CreateDirectInit_h
// semantic
#include "smtc_InitPtr.h"

// gram
#include "gram_BlockVector.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  InitPtr createDirectInit (util::Loc const & loc, gram::BlockVector const & block_set);
}
#undef LZZ_INLINE
#endif
