// smtc_CreateTmplFuncDecl.h
//

#ifndef LZZ_smtc_CreateTmplFuncDecl_h
#define LZZ_smtc_CreateTmplFuncDecl_h
// semantic
#include "smtc_FuncDeclPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ThrowSpecPtr.h"
#include "smtc_TmplFuncDeclPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Linkage;
}
namespace smtc
{
  class CvType;
}
namespace smtc
{
  class Cv;
}
namespace smtc
{
  TmplFuncDeclPtr createTmplFuncDecl (TmplSpecPtrVector const & tmpl_spec_set, Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
}
namespace smtc
{
  TmplFuncDeclPtr createTmplFuncDecl (TmplSpecPtrVector const & tmpl_spec_set, FuncDeclPtr const & func_decl);
}
#undef LZZ_INLINE
#endif
