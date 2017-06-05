// smtc_PrintNsFuncDefn.h
//

#ifndef LZZ_smtc_PrintNsFuncDefn_h
#define LZZ_smtc_PrintNsFuncDefn_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_FuncDeclPtr.h"
#include "smtc_FuncDefnPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsFuncDefn (Output & out, FuncDefnPtr const & func_defn, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
