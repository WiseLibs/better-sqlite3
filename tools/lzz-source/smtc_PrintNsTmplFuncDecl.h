// smtc_PrintNsTmplFuncDecl.h
//

#ifndef LZZ_smtc_PrintNsTmplFuncDecl_h
#define LZZ_smtc_PrintNsTmplFuncDecl_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_TmplFuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsTmplFuncDecl (Output & out, TmplFuncDeclPtr const & tmpl_func_decl, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
