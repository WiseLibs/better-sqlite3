// smtc_PrintNsClassInst.h
//

#ifndef LZZ_smtc_PrintNsClassInst_h
#define LZZ_smtc_PrintNsClassInst_h
#include "smtc_ClassDeclPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsClassInst (Output & out, ClassDeclPtr const & class_decl, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
