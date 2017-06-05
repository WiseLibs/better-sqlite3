// smtc_PrintMbrFuncDefn.h
//

#ifndef LZZ_smtc_PrintMbrFuncDefn_h
#define LZZ_smtc_PrintMbrFuncDefn_h
// semantic
#include "smtc_FuncDefnPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printMbrFuncDefn (Output & out, FuncDefnPtr const & func_defn, NsPtr const & ns, NamePtr const & qual_name);
}
#undef LZZ_INLINE
#endif
