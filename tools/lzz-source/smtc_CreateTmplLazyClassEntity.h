// smtc_CreateTmplLazyClassEntity.h
//

#ifndef LZZ_smtc_CreateTmplLazyClassEntity_h
#define LZZ_smtc_CreateTmplLazyClassEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TmplLazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplLazyClassEntity (TmplLazyClassPtr const & tmpl_lazy_class);
}
#undef LZZ_INLINE
#endif
