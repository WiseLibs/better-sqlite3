// smtc_LazyBaseSpecPtr.h
//

#ifndef LZZ_smtc_LazyBaseSpecPtr_h
#define LZZ_smtc_LazyBaseSpecPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class LazyBaseSpec;
}
namespace smtc
{
  typedef util::BPtr <LazyBaseSpec> LazyBaseSpecPtr;
}
#undef LZZ_INLINE
#endif
