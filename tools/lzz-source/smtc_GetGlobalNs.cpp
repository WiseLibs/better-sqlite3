// smtc_GetGlobalNs.cpp
//

#include "smtc_GetGlobalNs.h"
// semantic
#include "smtc_CreateGlobalNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr getGlobalNs ()
  {
    return createGlobalNs ();
  }
}
#undef LZZ_INLINE
