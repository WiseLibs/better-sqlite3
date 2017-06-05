// smtc_PrintMbrLazyClass.h
//

#ifndef LZZ_smtc_PrintMbrLazyClass_h
#define LZZ_smtc_PrintMbrLazyClass_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_LazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrLazyClass (FilePtr const & file, LazyClassPtr const & lazy_class);
}
#undef LZZ_INLINE
#endif
