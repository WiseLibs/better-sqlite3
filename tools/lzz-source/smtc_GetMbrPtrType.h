// smtc_GetMbrPtrType.h
//

#ifndef LZZ_smtc_GetMbrPtrType_h
#define LZZ_smtc_GetMbrPtrType_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_TypePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getMbrPtrType (NamePtr const & mbr_name, CvType const & to_cv_type);
}
#undef LZZ_INLINE
#endif
