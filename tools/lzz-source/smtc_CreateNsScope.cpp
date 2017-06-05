// smtc_CreateNsScope.cpp
//

#include "smtc_CreateNsScope.h"
// semantic
#include "smtc_NsScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createNsScope (NsPtr const & ns)
  {
    return new NsScope (ns);
  }
}
#undef LZZ_INLINE
