// smtc_TryBlockPtr.h
//

#ifndef LZZ_smtc_TryBlockPtr_h
#define LZZ_smtc_TryBlockPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TryBlock;
}
namespace smtc
{
  typedef util::BPtr <TryBlock> TryBlockPtr;
}
#undef LZZ_INLINE
#endif
