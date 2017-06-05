// smtc_CreateTmplSpecScope.cpp
//

#include "smtc_CreateTmplSpecScope.h"
// semantic
#include "smtc_TmplSpecScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createTmplSpecScope (ScopePtr const & parent, TmplSpecPtr const & tmpl_spec)
  {
    return new TmplSpecScope (parent, tmpl_spec);
  }
}
#undef LZZ_INLINE
