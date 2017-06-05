// smtc_EnumtorPtr.h
//

#ifndef LZZ_smtc_EnumtorPtr_h
#define LZZ_smtc_EnumtorPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Enumtor;
}
namespace smtc
{
  typedef util::BPtr <Enumtor> EnumtorPtr;
}
#undef LZZ_INLINE
#endif
