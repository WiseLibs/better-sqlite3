// smtc_CreateCtorInit.h
//

#ifndef LZZ_smtc_CreateCtorInit_h
#define LZZ_smtc_CreateCtorInit_h
// semantic
#include "smtc_CtorInitPtr.h"
#include "smtc_MbrInitPtrVector.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  CtorInitPtr createCtorInit (util::Loc const & loc, MbrInitPtrVector const & mbr_init_set);
}
#undef LZZ_INLINE
#endif
