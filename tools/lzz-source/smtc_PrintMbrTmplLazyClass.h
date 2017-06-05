// smtc_PrintMbrTmplLazyClass.h
//

#ifndef LZZ_smtc_PrintMbrTmplLazyClass_h
#define LZZ_smtc_PrintMbrTmplLazyClass_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_TmplLazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplLazyClass (FilePtr const & file, TmplLazyClassPtr const & tmpl_lazy_class);
}
#undef LZZ_INLINE
#endif
