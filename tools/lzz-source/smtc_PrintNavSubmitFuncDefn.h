// smtc_PrintNavSubmitFuncDefn.h
//

#ifndef LZZ_smtc_PrintNavSubmitFuncDefn_h
#define LZZ_smtc_PrintNavSubmitFuncDefn_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_NavSubmitFuncDefnPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNavSubmitFuncDefn (Output & out, NavSubmitFuncDefnPtr const & func_defn, NsPtr const & ns, NamePtr const & qual_name);
}
#undef LZZ_INLINE
#endif
