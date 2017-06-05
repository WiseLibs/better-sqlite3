// smtc_LazyClassScope.h
//

#ifndef LZZ_smtc_LazyClassScope_h
#define LZZ_smtc_LazyClassScope_h
// semantic
#include "smtc_ClassScope.h"
#include "smtc_LazyClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class LazyClassScope : public ClassScope
  {
  public:
    LazyClassScope (LazyClassPtr const & lazy_class);
    ~ LazyClassScope ();
    void accept (ScopeVisitor const & visitor) const;
    LazyClassPtr getLazyClass () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_LazyClassScope.inl"
#endif
#endif
