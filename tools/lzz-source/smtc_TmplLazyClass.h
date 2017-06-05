// smtc_TmplLazyClass.h
//

#ifndef LZZ_smtc_TmplLazyClass_h
#define LZZ_smtc_TmplLazyClass_h
// semantic
#include "smtc_LazyClassPtr.h"
#include "smtc_TmplClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplLazyClass : public TmplClassDefn
  {
  public:
    TmplLazyClass (TmplSpecPtrVector const & tmpl_spec_set, LazyClassPtr const & lazy_class);
    ~ TmplLazyClass ();
    LazyClassPtr getLazyClass () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplLazyClass.inl"
#endif
#endif
