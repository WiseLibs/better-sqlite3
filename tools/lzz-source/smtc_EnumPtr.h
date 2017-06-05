// smtc_EnumPtr.h
//

#ifndef LZZ_smtc_EnumPtr_h
#define LZZ_smtc_EnumPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Enum;
}
namespace smtc
{
  typedef util::BPtr <Enum> EnumPtr;
}
#undef LZZ_INLINE
#endif
