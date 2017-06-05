// smtc_GetUserType.cpp
//

#include "smtc_GetUserType.h"
// semantic
#include "smtc_UserType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getUserType (NamePtr const & name)
  {
    return new UserType (name);
  }
}
#undef LZZ_INLINE
