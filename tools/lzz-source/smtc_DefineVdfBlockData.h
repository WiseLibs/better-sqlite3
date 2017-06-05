// smtc_DefineVdfBlockData.h
//

#ifndef LZZ_smtc_DefineVdfBlockData_h
#define LZZ_smtc_DefineVdfBlockData_h
// semantic
#include "smtc_ScopePtr.h"
#include "smtc_ParamPtrVector.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#include "util_String.h"

#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr defineVdfBlockData (ScopePtr const & scope, util::Loc const & loc, util::Ident const & ident, ParamPtrVector const & param_set, bool vararg);
}
namespace smtc
{
  ScopePtr defineVdfBlockData (ScopePtr const & scope, util::Loc const & loc, util::String const & str, ParamPtrVector const & param_set, bool vararg);
}
#undef LZZ_INLINE
#endif
