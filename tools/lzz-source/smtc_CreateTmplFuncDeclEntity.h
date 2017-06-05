// smtc_CreateTmplFuncDeclEntity.h
//

#ifndef LZZ_smtc_CreateTmplFuncDeclEntity_h
#define LZZ_smtc_CreateTmplFuncDeclEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TmplFuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl);
}
#undef LZZ_INLINE
#endif
