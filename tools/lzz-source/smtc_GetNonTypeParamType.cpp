// smtc_GetNonTypeParamType.cpp
//

#include "smtc_GetNonTypeParamType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_GetNonTypeParamType.inl"
#endif
// semantic
#include "smtc_NonTypeParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType GetNonTypeParamType::operator () (ParamPtr const & param) const
  {
    return static_cast <NonTypeParam const &> (* param).getCvType ();
  }
}
namespace smtc
{
  GetNonTypeParamType::~ GetNonTypeParamType ()
         {}
}
#undef LZZ_INLINE
