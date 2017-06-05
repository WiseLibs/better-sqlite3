// smtc_DeclareAccessSpec.h
//

#ifndef LZZ_smtc_DeclareAccessSpec_h
#define LZZ_smtc_DeclareAccessSpec_h
// semantic
#include "smtc_Access.h"
#include "smtc_ScopePtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareAccessSpec (ScopePtr const & scope, util::Loc const & loc, Access access);
}
#undef LZZ_INLINE
#endif
