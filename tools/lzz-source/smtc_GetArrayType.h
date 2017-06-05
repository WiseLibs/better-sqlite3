// smtc_GetArrayType.h
//

#ifndef LZZ_smtc_GetArrayType_h
#define LZZ_smtc_GetArrayType_h
// semantic
#include "smtc_TypePtr.h"
#include "smtc_CvType.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getArrayType (CvType const & elem_cv_type, util::String const & size);
}
#undef LZZ_INLINE
#endif
