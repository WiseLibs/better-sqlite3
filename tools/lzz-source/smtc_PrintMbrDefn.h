// smtc_PrintMbrDefn.h
//

#ifndef LZZ_smtc_PrintMbrDefn_h
#define LZZ_smtc_PrintMbrDefn_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printMbrDefn (Output & out, ClassDefnPtr const & class_defn, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
