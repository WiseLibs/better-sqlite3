// smtc_TmplSpecScope.h
//

#ifndef LZZ_smtc_TmplSpecScope_h
#define LZZ_smtc_TmplSpecScope_h
// semantic
#include "smtc_Scope.h"
#include "smtc_ScopePtr.h"
#include "smtc_TmplSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplSpecScope : public Scope
  {
    ScopePtr m_parent;
    TmplSpecPtr m_tmpl_spec;
  public:
    TmplSpecScope (ScopePtr const & parent, TmplSpecPtr const & tmpl_spec);
    ~ TmplSpecScope ();
    void accept (ScopeVisitor const & visitor) const;
    ScopePtr const & getParent () const;
    TmplSpecPtr const & getTmplSpec () const;
  };
}
#undef LZZ_INLINE
#endif
