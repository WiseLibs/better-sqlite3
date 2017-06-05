// smtc_TdefPtr.h
//

#ifndef LZZ_smtc_TdefPtr_h
#define LZZ_smtc_TdefPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Tdef;
}
namespace smtc
{
  typedef util::BPtr <Tdef> TdefPtr;
}
#undef LZZ_INLINE
#endif
