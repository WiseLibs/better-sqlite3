// smtc_CreateBaseSpec.cpp
//

#include "smtc_CreateBaseSpec.h"
// semantic
#include "smtc_BaseSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpecPtr createBaseSpec (Access access, bool is_virtual, NamePtr const & base_name)
  {
    return new BaseSpec (access, is_virtual, base_name);
  }
}
#undef LZZ_INLINE
