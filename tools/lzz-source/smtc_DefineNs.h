// smtc_DefineNs.h
//

#ifndef LZZ_smtc_DefineNs_h
#define LZZ_smtc_DefineNs_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr defineNs (ScopePtr const & scope, util::Loc const & loc, NamePtr const & name);
}
namespace smtc
{
  ScopePtr defineUnnamedNs (ScopePtr const & scope, util::Loc const & loc);
}
#undef LZZ_INLINE
#endif
