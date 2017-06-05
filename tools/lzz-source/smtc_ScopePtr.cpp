// smtc_ScopePtr.cpp
//

#include "smtc_ScopePtr.h"
#include "smtc_Scope.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Scope>;
#undef LZZ_INLINE
