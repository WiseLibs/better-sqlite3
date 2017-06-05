// smtc_CreateFuncDecl.cpp
//

#include "smtc_CreateFuncDecl.h"
// semantic
#include "smtc_FuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  FuncDeclPtr createFuncDecl (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
  {
    return new FuncDecl (linkage, flags, ret_type, name, param_set, vararg, cv, throw_spec);
  }
}
#undef LZZ_INLINE
