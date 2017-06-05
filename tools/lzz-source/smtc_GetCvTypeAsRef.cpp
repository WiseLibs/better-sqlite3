// smtc_GetCvTypeAsRef.cpp
//

#include "smtc_GetCvTypeAsRef.h"
// semantic
#include "smtc_GetRefType.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType getCvTypeAsRef (CvType const & cv_type)
  {
    CvType res_cv_type = cv_type;
    if (res_cv_type.getType ()->getKind () != REF_TYPE)
    {
      res_cv_type = CvType (getRefType (res_cv_type));
    }
    return res_cv_type;
  }
}
#undef LZZ_INLINE
