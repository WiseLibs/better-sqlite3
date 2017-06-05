// smtc_NonTypeParamPtr.h
//

#ifndef LZZ_smtc_NonTypeParamPtr_h
#define LZZ_smtc_NonTypeParamPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Param;
}
namespace smtc
{
  class NonTypeParam;
}
namespace smtc
{
  typedef util::DPtr <NonTypeParam, Param> NonTypeParamPtr;
}
#undef LZZ_INLINE
#endif
