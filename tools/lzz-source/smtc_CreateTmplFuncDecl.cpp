// smtc_CreateTmplFuncDecl.cpp
//

#include "smtc_CreateTmplFuncDecl.h"
// semantic
#include "smtc_CreateFuncDecl.h"
#include "smtc_TmplFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplFuncDeclPtr createTmplFuncDecl (TmplSpecPtrVector const & tmpl_spec_set, Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
  {
    FuncDeclPtr func_decl = createFuncDecl (linkage, flags, ret_type, name, param_set, vararg, cv, throw_spec);
    return createTmplFuncDecl (tmpl_spec_set, func_decl);
  }
}
namespace smtc
{
  TmplFuncDeclPtr createTmplFuncDecl (TmplSpecPtrVector const & tmpl_spec_set, FuncDeclPtr const & func_decl)
  {
    return new TmplFuncDecl (tmpl_spec_set, func_decl);
  }
}
#undef LZZ_INLINE
