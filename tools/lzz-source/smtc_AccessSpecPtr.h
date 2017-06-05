// smtc_AccessSpecPtr.h
//

#ifndef LZZ_smtc_AccessSpecPtr_h
#define LZZ_smtc_AccessSpecPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class AccessSpec;
}
namespace smtc
{
  typedef util::BPtr <AccessSpec> AccessSpecPtr;
}
#undef LZZ_INLINE
#endif
