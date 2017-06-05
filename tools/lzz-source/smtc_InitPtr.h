// smtc_InitPtr.h
//

#ifndef LZZ_smtc_InitPtr_h
#define LZZ_smtc_InitPtr_h
// util
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Init;
}
namespace smtc
{
  typedef util::BPtr <Init> InitPtr;
}
#undef LZZ_INLINE
#endif
