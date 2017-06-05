// smtc_OpenLinkageSpec.cpp
//

#include "smtc_OpenLinkageSpec.h"
// semantic
#include "smtc_Linkage.h"
#include "smtc_CreateLinkageSpecScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr openLinkageSpec (ScopePtr const & encl_scope, util::Loc const & loc, util::Ident const & lang)
  {
    // enclosing scope is namespace scope
    ScopePtr res_scope = createLinkageSpecScope (encl_scope, loc, Linkage (lang));
    return res_scope;
  }
}
#undef LZZ_INLINE
