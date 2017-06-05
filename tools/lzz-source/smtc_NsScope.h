// smtc_NsScope.h
//

#ifndef LZZ_smtc_NsScope_h
#define LZZ_smtc_NsScope_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_Scope.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NsScope : public Scope
  {
    NsPtr m_ns;
  public:
    NsScope (NsPtr const & ns);
    ~ NsScope ();
    void accept (ScopeVisitor const & visitor) const;
    NsPtr const & getNs () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NsScope.inl"
#endif
#endif
