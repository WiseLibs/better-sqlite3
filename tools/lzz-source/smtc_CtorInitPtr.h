// smtc_CtorInitPtr.h
//

#ifndef LZZ_smtc_CtorInitPtr_h
#define LZZ_smtc_CtorInitPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class CtorInit;
}
namespace smtc
{
  typedef util::BPtr <CtorInit> CtorInitPtr;
}
#undef LZZ_INLINE
#endif
