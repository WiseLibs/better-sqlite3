// smtc_GetMbrPtrType.cpp
//

#include "smtc_GetMbrPtrType.h"
// semantic
#include "smtc_MbrPtrType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getMbrPtrType (NamePtr const & mbr_name, CvType const & to_cv_type)
  {
    return new MbrPtrType (mbr_name, to_cv_type);
  }
}
#undef LZZ_INLINE
