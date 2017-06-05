// smtc_CreateTmplFuncDefn.h
//

#ifndef LZZ_smtc_CreateTmplFuncDefn_h
#define LZZ_smtc_CreateTmplFuncDefn_h
// semantic
#include "smtc_CtorInitPtr.h"
#include "smtc_FuncDefnPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ThrowSpecPtr.h"
#include "smtc_TmplFuncDefnPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#include "smtc_TryBlockPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  class Block;
}
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
  TmplFuncDefnPtr createTmplFuncDefn (TmplSpecPtrVector const & tmpl_spec_set, Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block);
}
namespace smtc
{
  TmplFuncDefnPtr createTmplFuncDefn (TmplSpecPtrVector const & tmpl_spec_set, FuncDefnPtr const & func_defn);
}
#undef LZZ_INLINE
#endif
