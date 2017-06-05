// smtc_CreateFrndTmplClassDeclEntity.cpp
//

#include "smtc_CreateFrndTmplClassDeclEntity.h"
// semantic
#include "smtc_FrndTmplClassDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndTmplClassDeclEntity (TmplClassDeclPtr const & tmpl_class_decl)
  {
    return new FrndTmplClassDeclEntity (tmpl_class_decl);
  }
}
#undef LZZ_INLINE
