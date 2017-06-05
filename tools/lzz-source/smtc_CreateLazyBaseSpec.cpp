// smtc_CreateLazyBaseSpec.cpp
//

#include "smtc_CreateLazyBaseSpec.h"
// semantic
#include "smtc_LazyBaseSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpecPtr createLazyBaseSpec (Access access, bool is_virtual, NamePtr const & base_name, gram::BlockVector const & arg_set)
  {
    return new LazyBaseSpec (access, is_virtual, base_name, arg_set);
  }
}
#undef LZZ_INLINE
