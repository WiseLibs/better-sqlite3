// smtc_BaseNamePtr.h
//

#ifndef LZZ_smtc_BaseNamePtr_h
#define LZZ_smtc_BaseNamePtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class BaseName;
}
namespace smtc
{
  typedef util::BPtr <BaseName> BaseNamePtr;
}
#undef LZZ_INLINE
#endif
