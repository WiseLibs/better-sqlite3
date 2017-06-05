// smtc_CreateFuncDefn.cpp
//

#include "smtc_CreateFuncDefn.h"
// semantic
#include "smtc_FuncDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  FuncDefnPtr createFuncDefn (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block)
  {
    return new FuncDefn (linkage, flags, ret_type, name, param_set, vararg, cv, throw_spec, ctor_init, body, try_block);
  }
}
#undef LZZ_INLINE
