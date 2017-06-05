// smtc_GetCv.h
//

#ifndef LZZ_smtc_GetCv_h
#define LZZ_smtc_GetCv_h
// semantic
#include "smtc_Cv.h"
#define LZZ_INLINE inline
namespace smtc
{
  Cv getCv (bool c, bool v);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_GetCv.inl"
#endif
#endif
