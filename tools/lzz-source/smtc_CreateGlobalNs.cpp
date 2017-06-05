// smtc_CreateGlobalNs.cpp
//

#include "smtc_CreateGlobalNs.h"
// semantic
#include "smtc_GlobalNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr createGlobalNs ()
  {
    return new GlobalNs ();
  }
}
#undef LZZ_INLINE
