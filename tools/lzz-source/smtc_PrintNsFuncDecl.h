// smtc_PrintNsFuncDecl.h
//

#ifndef LZZ_smtc_PrintNsFuncDecl_h
#define LZZ_smtc_PrintNsFuncDecl_h
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
  void printNsFuncDecl (Output & out, FuncDeclPtr const & func, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
