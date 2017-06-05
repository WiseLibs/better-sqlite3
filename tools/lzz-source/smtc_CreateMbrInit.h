// smtc_CreateMbrInit.h
//

#ifndef LZZ_smtc_CreateMbrInit_h
#define LZZ_smtc_CreateMbrInit_h
// semantic
#include "smtc_MbrInitPtr.h"
#include "smtc_NamePtr.h"

// gram
#include "gram_BlockVector.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  MbrInitPtr createMbrInit (NamePtr const & name, util::String const & arg_set);
}
namespace smtc
{
  MbrInitPtr createMbrInit (NamePtr const & name, gram::BlockVector const & arg_set);
}
#undef LZZ_INLINE
#endif
