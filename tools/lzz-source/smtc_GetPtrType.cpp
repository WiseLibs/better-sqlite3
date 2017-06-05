// smtc_GetPtrType.cpp
//

#include "smtc_GetPtrType.h"
// semantic
#include "smtc_PtrType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getPtrType (CvType const & to_cv_type)
  {
    return new PtrType (to_cv_type);
  }
}
#undef LZZ_INLINE
