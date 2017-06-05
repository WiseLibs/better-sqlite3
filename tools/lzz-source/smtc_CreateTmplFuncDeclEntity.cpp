// smtc_CreateTmplFuncDeclEntity.cpp
//

#include "smtc_CreateTmplFuncDeclEntity.h"
// semantic
#include "smtc_TmplFuncDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl)
  {
    return new TmplFuncDeclEntity (tmpl_func_decl);
  }
}
#undef LZZ_INLINE
