// smtc_PrintMbrTmplLazyClass.cpp
//

#include "smtc_PrintMbrTmplLazyClass.h"
// semantic
#include "smtc_CompleteLazyClass.h"
#include "smtc_PrintMbrTmplClassDefn.h"
#include "smtc_TmplLazyClass.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplLazyClass (FilePtr const & file, TmplLazyClassPtr const & tmpl_lazy_class)
  {
    completeLazyClass (tmpl_lazy_class->getLazyClass ());
    printMbrTmplClassDefn (file, tmpl_lazy_class);
  }
}
#undef LZZ_INLINE
