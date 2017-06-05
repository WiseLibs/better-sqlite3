// smtc_OpenTmplSpec.h
//

#ifndef LZZ_smtc_OpenTmplSpec_h
#define LZZ_smtc_OpenTmplSpec_h
// semantic
#include "smtc_ScopePtr.h"
#include "smtc_ParamPtrVector.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr openTmplSpec (ScopePtr const & scope, util::Loc const & loc, ParamPtrVector const & param_set);
}
#undef LZZ_INLINE
#endif
