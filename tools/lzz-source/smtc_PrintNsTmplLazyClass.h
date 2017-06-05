// smtc_PrintNsTmplLazyClass.h
//

#ifndef LZZ_smtc_PrintNsTmplLazyClass_h
#define LZZ_smtc_PrintNsTmplLazyClass_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_TmplLazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsTmplLazyClass (Output & out, TmplLazyClassPtr const & tmpl_lazy_class, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
