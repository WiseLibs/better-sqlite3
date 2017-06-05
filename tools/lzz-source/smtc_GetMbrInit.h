// smtc_GetMbrInit.h
//

#ifndef LZZ_smtc_GetMbrInit_h
#define LZZ_smtc_GetMbrInit_h
// semantic
#include "smtc_MbrInitPtr.h"
#include "smtc_NamePtr.h"

// gram
#include "gram_BlockVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  MbrInitPtr getMbrInit (NamePtr const & name, gram::BlockVector const & arg_set);
}
#undef LZZ_INLINE
#endif
