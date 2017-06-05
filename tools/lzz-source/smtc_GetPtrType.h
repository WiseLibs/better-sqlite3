// smtc_GetPtrType.h
//

#ifndef LZZ_smtc_GetPtrType_h
#define LZZ_smtc_GetPtrType_h
// semantic
#include "smtc_TypePtr.h"
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getPtrType (CvType const & to_cv_type);
}
#undef LZZ_INLINE
#endif
