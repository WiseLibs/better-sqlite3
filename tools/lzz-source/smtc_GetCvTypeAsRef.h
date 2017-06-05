// smtc_GetCvTypeAsRef.h
//

#ifndef LZZ_smtc_GetCvTypeAsRef_h
#define LZZ_smtc_GetCvTypeAsRef_h
// semantic
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType getCvTypeAsRef (CvType const & cv_type);
}
#undef LZZ_INLINE
#endif
