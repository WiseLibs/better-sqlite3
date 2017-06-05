// smtc_GetLazyBaseSpec.cpp
//

#include "smtc_GetLazyBaseSpec.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_CreateLazyBaseSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpecPtr getLazyBaseSpec (Access access, bool is_virtual, NamePtr const & base_name, gram::BlockVector const & arg_set)
  {
    std::for_each (arg_set.begin (), arg_set.end (), gram::TrimBlock ());
    return createLazyBaseSpec (access, is_virtual, base_name, arg_set);
  }
}
#undef LZZ_INLINE
