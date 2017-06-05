// smtc_IsObjStaticConstIntegral.h
//

#ifndef LZZ_smtc_IsObjStaticConstIntegral_h
#define LZZ_smtc_IsObjStaticConstIntegral_h
// semantic
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool isObjConstIntegral (ObjPtr const & obj);
}
namespace smtc
{
  bool isObjStaticConstIntegral (ObjPtr const & obj);
}
#undef LZZ_INLINE
#endif
