// smtc_OpenLinkageSpec.h
//

#ifndef LZZ_smtc_OpenLinkageSpec_h
#define LZZ_smtc_OpenLinkageSpec_h
// semantic
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace util
{
  class Ident;
}
namespace util
{
  class Loc;
}
namespace smtc
{
  ScopePtr openLinkageSpec (ScopePtr const & encl_scope, util::Loc const & loc, util::Ident const & lang);
}
#undef LZZ_INLINE
#endif
