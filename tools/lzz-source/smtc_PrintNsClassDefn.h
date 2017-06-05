// smtc_PrintNsClassDefn.h
//

#ifndef LZZ_smtc_PrintNsClassDefn_h
#define LZZ_smtc_PrintNsClassDefn_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsClassDefn (Output & out, ClassDefnPtr const & class_defn, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
