// smtc_CreateTmplClassDeclEntity.cpp
//

#include "smtc_CreateTmplClassDeclEntity.h"
// semantic
#include "smtc_TmplClassDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplClassDeclEntity (TmplClassDeclPtr const & tmpl_class_decl)
  {
    return new TmplClassDeclEntity (tmpl_class_decl);
  }
}
#undef LZZ_INLINE
