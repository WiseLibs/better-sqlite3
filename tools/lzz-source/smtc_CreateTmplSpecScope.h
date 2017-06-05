// smtc_CreateTmplSpecScope.h
//

#ifndef LZZ_smtc_CreateTmplSpecScope_h
#define LZZ_smtc_CreateTmplSpecScope_h
// semantic
#include "smtc_TmplSpecPtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createTmplSpecScope (ScopePtr const & parent, TmplSpecPtr const & tmpl_spec);
}
#undef LZZ_INLINE
#endif
