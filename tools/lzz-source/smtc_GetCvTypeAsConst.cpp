// smtc_GetCvTypeAsConst.cpp
//

#include "smtc_GetCvTypeAsConst.h"
// semantic
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType getCvTypeAsConst (CvType const & cv_type)
  {
    CvType res_cv_type = cv_type;
    if (res_cv_type.getType ()->getKind () != REF_TYPE)
    {
      Cv const & cv = res_cv_type.getCv ();
      res_cv_type = CvType (res_cv_type.getType (), Cv (true, cv.isVolatile ()));
    }
    return res_cv_type;
  }
}
#undef LZZ_INLINE
