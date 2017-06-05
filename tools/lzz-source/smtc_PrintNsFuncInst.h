// smtc_PrintNsFuncInst.h
//

#ifndef LZZ_smtc_PrintNsFuncInst_h
#define LZZ_smtc_PrintNsFuncInst_h
// semantic
#include "smtc_FuncDeclPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsFuncInst (Output & out, FuncDeclPtr const & func_decl, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
