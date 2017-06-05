// smtc_CreateCtorInit.cpp
//

#include "smtc_CreateCtorInit.h"
// semantic
#include "smtc_CtorInit.h"
#define LZZ_INLINE inline
namespace smtc
{
  CtorInitPtr createCtorInit (util::Loc const & loc, MbrInitPtrVector const & mbr_init_set)
  {
    return new CtorInit (loc, mbr_init_set);
  }
}
#undef LZZ_INLINE
