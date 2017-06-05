// smtc_CreateLazyClassEntity.cpp
//

#include "smtc_CreateLazyClassEntity.h"
// semantic
#include "smtc_LazyClassEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createLazyClassEntity (LazyClassPtr const & lazy_class)
  {
    return new LazyClassEntity (lazy_class);
  }
}
#undef LZZ_INLINE
