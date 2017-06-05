// smtc_BaseSpecPtr.h
//

#ifndef LZZ_smtc_BaseSpecPtr_h
#define LZZ_smtc_BaseSpecPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class BaseSpec;
}
namespace smtc
{
  typedef util::BPtr <BaseSpec> BaseSpecPtr;
}
#undef LZZ_INLINE
#endif
