// smtc_ThrowSpecPtr.h
//

#ifndef LZZ_smtc_ThrowSpecPtr_h
#define LZZ_smtc_ThrowSpecPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ThrowSpec;
}
namespace smtc
{
  typedef util::BPtr <ThrowSpec> ThrowSpecPtr;
}
#undef LZZ_INLINE
#endif
