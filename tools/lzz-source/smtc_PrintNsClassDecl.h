// smtc_PrintNsClassDecl.h
//

#ifndef LZZ_smtc_PrintNsClassDecl_h
#define LZZ_smtc_PrintNsClassDecl_h
// semantic
#include "smtc_ClassDeclPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsClassDecl (Output & out, ClassDeclPtr const & class_decl, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
