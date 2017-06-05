// smtc_IsIntegralType.cpp
//

#include "smtc_IsIntegralType.h"
// semantic
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool isIntegralType (TypePtr const & type)
  {
    TypeKind kind = type->getKind ();
    return kind >= BOOL_TYPE && kind <= UNSIGNED_LONG_LONG_INT_TYPE;
  }
}
#undef LZZ_INLINE
