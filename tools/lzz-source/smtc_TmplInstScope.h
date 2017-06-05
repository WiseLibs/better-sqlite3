// smtc_TmplInstScope.h
//

#ifndef LZZ_smtc_TmplInstScope_h
#define LZZ_smtc_TmplInstScope_h
// semantic
#include "smtc_Scope.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplInstScope : public Scope
  {
    ScopePtr m_parent;
  public:
    TmplInstScope (ScopePtr const & parent);
    ~ TmplInstScope ();
    void accept (ScopeVisitor const & visitor) const;
    ScopePtr const & getParent () const;
  };
}
#undef LZZ_INLINE
#endif
