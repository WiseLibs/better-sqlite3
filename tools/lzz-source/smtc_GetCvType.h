// smtc_GetCvType.h
//

#ifndef LZZ_smtc_GetCvType_h
#define LZZ_smtc_GetCvType_h
// semantic
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType getCvType (TypePtr const & type, bool c, bool v);
}
namespace smtc
{
  CvType getCvType (TypePtr const & type, Cv const & cv = Cv ());
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_GetCvType.inl"
#endif
#endif
