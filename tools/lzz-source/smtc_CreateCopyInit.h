// smtc_CreateCopyInit.h
//

#ifndef LZZ_smtc_CreateCopyInit_h
#define LZZ_smtc_CreateCopyInit_h
// semantic
#include "smtc_InitPtr.h"

// gram
#include "gram_Block.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  InitPtr createCopyInit (util::Loc const & loc, gram::Block const & block);
}
#undef LZZ_INLINE
#endif
