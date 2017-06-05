// smtc_PrintNsVdfDataFuncDefn.h
//

#ifndef LZZ_smtc_PrintNsVdfDataFuncDefn_h
#define LZZ_smtc_PrintNsVdfDataFuncDefn_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_VdfDataFuncDefnPtr.h"

#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsVdfDataFuncDefn (Output & out, VdfDataFuncDefnPtr const & func_defn, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
