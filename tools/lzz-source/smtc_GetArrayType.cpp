// smtc_GetArrayType.cpp
//

#include "smtc_GetArrayType.h"
// semantic
#include "smtc_ArrayType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getArrayType (CvType const & elem_cv_type, util::String const & size)
  {
    return new ArrayType (elem_cv_type, size);
  }
}
#undef LZZ_INLINE
