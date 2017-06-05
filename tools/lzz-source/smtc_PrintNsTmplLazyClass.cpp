// smtc_PrintNsTmplLazyClass.cpp
//

#include "smtc_PrintNsTmplLazyClass.h"
// semantic
#include "smtc_CompleteLazyClass.h"
#include "smtc_PrintNsTmplClassDefn.h"
#include "smtc_TmplLazyClass.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsTmplLazyClass (Output & out, TmplLazyClassPtr const & tmpl_lazy_class, NsPtr const & ns)
  {
    completeLazyClass (tmpl_lazy_class->getLazyClass ());
    printNsTmplClassDefn (out, tmpl_lazy_class, ns);
  }
}
#undef LZZ_INLINE
