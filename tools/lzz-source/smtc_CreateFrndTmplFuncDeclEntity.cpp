// smtc_CreateFrndTmplFuncDeclEntity.cpp
//

#include "smtc_CreateFrndTmplFuncDeclEntity.h"
// semantic
#include "smtc_FrndTmplFuncDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndTmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl)
  {
    return new FrndTmplFuncDeclEntity (tmpl_func_decl);
  }
}
#undef LZZ_INLINE
