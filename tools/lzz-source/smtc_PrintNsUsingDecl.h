// smtc_PrintNsUsingDecl.h
//

#ifndef LZZ_smtc_PrintNsUsingDecl_h
#define LZZ_smtc_PrintNsUsingDecl_h
// semantic
#include "smtc_UsingDeclPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsUsingDecl (Output & out, UsingDeclPtr const & using_decl, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
