// smtc_PrintNsLazyClass.cpp
//

#include "smtc_PrintNsLazyClass.h"
// semantic
#include "smtc_CompleteLazyClass.h"
#include "smtc_PrintNsClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsLazyClass (Output & out, LazyClassPtr const & lazy_class, NsPtr const & ns)
  {
    completeLazyClass (lazy_class);
    printNsClassDefn (out, lazy_class, ns);
  }
}
#undef LZZ_INLINE
