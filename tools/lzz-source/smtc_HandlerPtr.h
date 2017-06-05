// smtc_HandlerPtr.h
//

#ifndef LZZ_smtc_HandlerPtr_h
#define LZZ_smtc_HandlerPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Handler;
}
namespace smtc
{
  typedef util::BPtr <Handler> HandlerPtr;
}
#undef LZZ_INLINE
#endif
