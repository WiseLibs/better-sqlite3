// smtc_GetBaseSpec.cpp
//

#include "smtc_GetBaseSpec.h"
// semantic
#include "smtc_CreateBaseSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpecPtr getBaseSpec (Access access, bool is_virtual, NamePtr const & base_name)
  {
    return createBaseSpec (access, is_virtual, base_name);
  }
}
#undef LZZ_INLINE
