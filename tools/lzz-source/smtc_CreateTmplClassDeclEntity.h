// smtc_CreateTmplClassDeclEntity.h
//

#ifndef LZZ_smtc_CreateTmplClassDeclEntity_h
#define LZZ_smtc_CreateTmplClassDeclEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TmplClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplClassDeclEntity (TmplClassDeclPtr const & tmpl_class_decl);
}
#undef LZZ_INLINE
#endif
