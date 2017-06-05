// smtc_IsObjStaticConstIntegral.cpp
//

#include "smtc_IsObjStaticConstIntegral.h"
// semantic
#include "smtc_IsIntegralType.h"
#include "smtc_Obj.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool isObjConstIntegral (ObjPtr const & obj)
  {
    CvType const & cv_type = obj->getCvType ();
    return cv_type.getCv ().isConstOnly () && isIntegralType (cv_type.getType ());
  }
}
namespace smtc
{
  bool isObjStaticConstIntegral (ObjPtr const & obj)
  {
    return obj->isStatic () && isObjConstIntegral (obj);
  }
}
#undef LZZ_INLINE
