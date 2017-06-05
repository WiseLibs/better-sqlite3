// smtc_ParamPtr.h
//

#ifndef LZZ_smtc_ParamPtr_h
#define LZZ_smtc_ParamPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Param;
}
namespace smtc
{
  typedef util::BPtr <Param> ParamPtr;
}
#undef LZZ_INLINE
#endif
