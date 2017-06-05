// smtc_LinkageSpecScope.h
//

#ifndef LZZ_smtc_LinkageSpecScope_h
#define LZZ_smtc_LinkageSpecScope_h
// semantic
#include "smtc_Scope.h"
#include "smtc_Linkage.h"
#include "smtc_ScopePtr.h"
// util
#include "util_Loc.h"
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  class LinkageSpecScope : public Scope
  {
    ScopePtr m_parent;
    util::Loc m_loc;
    Linkage m_linkage;
  public:
    LinkageSpecScope (ScopePtr const & parent, util::Loc const & loc, Linkage const & linkage);
    ~ LinkageSpecScope ();
    void accept (ScopeVisitor const & visitor) const;
    ScopePtr const & getParent () const;
    util::Loc const & getLoc () const;
    Linkage const & getLinkage () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_LinkageSpecScope.inl"
#endif
#endif
