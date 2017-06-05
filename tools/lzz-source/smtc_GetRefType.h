// smtc_GetRefType.h
//

#ifndef LZZ_smtc_GetRefType_h
#define LZZ_smtc_GetRefType_h
// semantic
#include "smtc_TypePtr.h"
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getRefType (CvType const & to_cv_type);
}
#undef LZZ_INLINE
#endif
