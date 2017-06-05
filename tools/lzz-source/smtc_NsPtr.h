// smtc_NsPtr.h
//

#ifndef LZZ_smtc_NsPtr_h
#define LZZ_smtc_NsPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Ns;
}
namespace smtc
{
  typedef util::BPtr <Ns> NsPtr;
}
#undef LZZ_INLINE
#endif
