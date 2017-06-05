// smtc_OpenLinkageBlock.h
//

#ifndef LZZ_smtc_OpenLinkageBlock_h
#define LZZ_smtc_OpenLinkageBlock_h
// semantic
#include "smtc_ScopePtr.h"
// util
#include "util_Loc.h"
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr openLinkageBlock (ScopePtr const & encl_scope, util::Loc const & loc, util::Ident const & linkage);
}
#undef LZZ_INLINE
#endif
