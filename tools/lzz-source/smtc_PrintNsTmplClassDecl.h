// smtc_PrintNsTmplClassDecl.h
//

#ifndef LZZ_smtc_PrintNsTmplClassDecl_h
#define LZZ_smtc_PrintNsTmplClassDecl_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_TmplClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsTmplClassDecl (Output & out, TmplClassDeclPtr const & tmpl_class_decl, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
