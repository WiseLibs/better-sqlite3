// smtc_LazyClassEntity.h
//

#ifndef LZZ_smtc_LazyClassEntity_h
#define LZZ_smtc_LazyClassEntity_h
// semantic
#include "smtc_ClassDefnEntity.h"
#include "smtc_LazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class LazyClassEntity : public ClassDefnEntity
  {
  public:
    LazyClassEntity (LazyClassPtr const & lazy_ctor);
    ~ LazyClassEntity ();
    void accept (EntityVisitor const & visitor) const;
    LazyClassPtr getLazyClass () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_LazyClassEntity.inl"
#endif
#endif
