// smtc_GetNonTypeParamType.h
//

#ifndef LZZ_smtc_GetNonTypeParamType_h
#define LZZ_smtc_GetNonTypeParamType_h
// semantic
#include "smtc_CvType.h"
#include "smtc_ParamPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct GetNonTypeParamType
  {
    CvType operator () (ParamPtr const & param) const;
  public:
    explicit GetNonTypeParamType ();
    ~ GetNonTypeParamType ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_GetNonTypeParamType.inl"
#endif
#endif
