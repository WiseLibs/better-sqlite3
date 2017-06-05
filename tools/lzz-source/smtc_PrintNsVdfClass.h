// smtc_PrintNsVdfClass.h
//

#ifndef LZZ_smtc_PrintNsVdfClass_h
#define LZZ_smtc_PrintNsVdfClass_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_ClassDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsVdfClass (Output & out, ClassDefnPtr const & class_defn, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
