// smtc_CreateFuncDefn.h
//

#ifndef LZZ_smtc_CreateFuncDefn_h
#define LZZ_smtc_CreateFuncDefn_h
// semantic
#include "smtc_CtorInitPtr.h"
#include "smtc_FuncDefnPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ThrowSpecPtr.h"
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
  FuncDefnPtr createFuncDefn (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block);
}
#undef LZZ_INLINE
#endif
