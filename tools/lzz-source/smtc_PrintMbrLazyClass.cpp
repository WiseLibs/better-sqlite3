// smtc_PrintMbrLazyClass.cpp
//

#include "smtc_PrintMbrLazyClass.h"
// semantic
#include "smtc_CompleteLazyClass.h"
#include "smtc_PrintMbrClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrLazyClass (FilePtr const & file, LazyClassPtr const & lazy_class)
  {
    completeLazyClass (lazy_class);
    printMbrClassDefn (file, lazy_class);
  }
}
#undef LZZ_INLINE
