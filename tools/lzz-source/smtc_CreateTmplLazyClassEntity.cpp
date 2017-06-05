// smtc_CreateTmplLazyClassEntity.cpp
//

#include "smtc_CreateTmplLazyClassEntity.h"
// semantic
#include "smtc_TmplLazyClassEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplLazyClassEntity (TmplLazyClassPtr const & tmpl_lazy_class)
  {
    return new TmplLazyClassEntity (tmpl_lazy_class);
  }
}
#undef LZZ_INLINE
