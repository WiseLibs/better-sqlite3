// smtc_BuildLazyClassMbrInitSet.h
//

#ifndef LZZ_smtc_BuildLazyClassMbrInitSet_h
#define LZZ_smtc_BuildLazyClassMbrInitSet_h
// semantic
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_MbrInitPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  void buildLazyClassMbrInitSet (BaseSpecPtrVector const & base_spec_set, MbrInitPtrVector & mbr_init_set);
}
#undef LZZ_INLINE
#endif
