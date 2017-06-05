// smtc_NavClassScope.h
//

#ifndef LZZ_smtc_NavClassScope_h
#define LZZ_smtc_NavClassScope_h
// semantic
#include "smtc_ClassScope.h"
#include "smtc_NavClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NavClassScope : public ClassScope
  {
  public:
    NavClassScope (NavClassPtr const & nav_class);
    ~ NavClassScope ();
    void accept (ScopeVisitor const & visitor) const;
    NavClassPtr getNavClass () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NavClassScope.inl"
#endif
#endif
