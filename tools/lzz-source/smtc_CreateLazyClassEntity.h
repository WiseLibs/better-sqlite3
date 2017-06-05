// smtc_CreateLazyClassEntity.h
//

#ifndef LZZ_smtc_CreateLazyClassEntity_h
#define LZZ_smtc_CreateLazyClassEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_LazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createLazyClassEntity (LazyClassPtr const & lazy_class);
}
#undef LZZ_INLINE
#endif
