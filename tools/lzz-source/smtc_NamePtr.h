// smtc_NamePtr.h
//

#ifndef LZZ_smtc_NamePtr_h
#define LZZ_smtc_NamePtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Name;
}
namespace smtc
{
  typedef util::BPtr <Name> NamePtr;
}
#undef LZZ_INLINE
#endif
