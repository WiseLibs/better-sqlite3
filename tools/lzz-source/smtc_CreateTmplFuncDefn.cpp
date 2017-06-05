// smtc_CreateTmplFuncDefn.cpp
//

#include "smtc_CreateTmplFuncDefn.h"
// semantic
#include "smtc_CreateFuncDefn.h"
#include "smtc_TmplFuncDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplFuncDefnPtr createTmplFuncDefn (TmplSpecPtrVector const & tmpl_spec_set, Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block)
  {
    FuncDefnPtr func_defn = createFuncDefn (linkage, flags, ret_type, name, param_set, vararg, cv, throw_spec, ctor_init, body, try_block);
    return createTmplFuncDefn (tmpl_spec_set, func_defn);
  }
}
namespace smtc
{
  TmplFuncDefnPtr createTmplFuncDefn (TmplSpecPtrVector const & tmpl_spec_set, FuncDefnPtr const & func_defn)
  {
    return new TmplFuncDefn (tmpl_spec_set, func_defn);
  }
}
#undef LZZ_INLINE
