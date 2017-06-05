// smtc_PrintNsLazyClass.h
//

#ifndef LZZ_smtc_PrintNsLazyClass_h
#define LZZ_smtc_PrintNsLazyClass_h
// semantic
#include "smtc_LazyClassPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsLazyClass (Output & out, LazyClassPtr const & lazy_class, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
