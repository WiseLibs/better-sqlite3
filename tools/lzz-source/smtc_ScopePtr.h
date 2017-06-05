// smtc_ScopePtr.h
//

#ifndef LZZ_smtc_ScopePtr_h
#define LZZ_smtc_ScopePtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Scope;
}
namespace smtc
{
  typedef util::BPtr <Scope> ScopePtr;
}
#undef LZZ_INLINE
#endif
