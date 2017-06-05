// smtc_CreateFrndTmplFuncDeclEntity.h
//

#ifndef LZZ_smtc_CreateFrndTmplFuncDeclEntity_h
#define LZZ_smtc_CreateFrndTmplFuncDeclEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TmplFuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndTmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl);
}
#undef LZZ_INLINE
#endif
