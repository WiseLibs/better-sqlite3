// smtc_GetCvTypeAsConst.h
//

#ifndef LZZ_smtc_GetCvTypeAsConst_h
#define LZZ_smtc_GetCvTypeAsConst_h
// semantic
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType getCvTypeAsConst (CvType const & cv_type);
}
#undef LZZ_INLINE
#endif
