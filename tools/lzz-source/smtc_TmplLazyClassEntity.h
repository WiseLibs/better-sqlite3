// smtc_TmplLazyClassEntity.h
//

#ifndef LZZ_smtc_TmplLazyClassEntity_h
#define LZZ_smtc_TmplLazyClassEntity_h
// semantic
#include "smtc_TmplClassDefnEntity.h"
#include "smtc_TmplLazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplLazyClassEntity : public TmplClassDefnEntity
  {
  public:
    TmplLazyClassEntity (TmplLazyClassPtr const & tmpl_lazy_class);
    ~ TmplLazyClassEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplLazyClassPtr getTmplLazyClass () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplLazyClassEntity.inl"
#endif
#endif
