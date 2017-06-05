// smtc_TypePtr.h
//

#ifndef LZZ_smtc_TypePtr_h
#define LZZ_smtc_TypePtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Type;
}
namespace smtc
{
  typedef util::BPtr <Type> TypePtr;
}
#undef LZZ_INLINE
#endif
