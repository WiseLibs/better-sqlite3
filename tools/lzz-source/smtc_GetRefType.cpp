// smtc_GetRefType.cpp
//

#include "smtc_GetRefType.h"
// semantic
#include "smtc_RefType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getRefType (CvType const & to_cv_type)
  {
    return new RefType (to_cv_type);
  }
}
#undef LZZ_INLINE
