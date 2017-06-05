// smtc_OpenTmplSpec.cpp
//

#include "smtc_OpenTmplSpec.h"
// semantic
#include "smtc_CreateTmplSpec.h"
#include "smtc_CreateTmplSpecScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr openTmplSpec (ScopePtr const & scope, util::Loc const & loc, ParamPtrVector const & param_set)
  {
    TmplSpecPtr tmpl_spec = createTmplSpec (loc, param_set);
    return createTmplSpecScope (scope.unref (), tmpl_spec);
  }
}
#undef LZZ_INLINE
