// smtc_CreateFuncDecl.h
//

#ifndef LZZ_smtc_CreateFuncDecl_h
#define LZZ_smtc_CreateFuncDecl_h
// semantic
#include "smtc_FuncDeclPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ThrowSpecPtr.h"
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
  FuncDeclPtr createFuncDecl (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
}
#undef LZZ_INLINE
#endif
