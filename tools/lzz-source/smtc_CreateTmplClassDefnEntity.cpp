// smtc_CreateTmplClassDefnEntity.cpp
//

#include "smtc_CreateTmplClassDefnEntity.h"
// semantic
#include "smtc_TmplClassDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplClassDefnEntity (TmplClassDefnPtr const & tmpl_class_defn)
  {
    return new TmplClassDefnEntity (tmpl_class_defn);
  }
}
#undef LZZ_INLINE
