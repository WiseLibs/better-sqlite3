// smtc_CreateTmplClassDefnEntity.h
//

#ifndef LZZ_smtc_CreateTmplClassDefnEntity_h
#define LZZ_smtc_CreateTmplClassDefnEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TmplClassDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplClassDefnEntity (TmplClassDefnPtr const & tmpl_class_defn);
}
#undef LZZ_INLINE
#endif
