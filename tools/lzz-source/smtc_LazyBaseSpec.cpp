// smtc_LazyBaseSpec.cpp
//

#include "smtc_LazyBaseSpec.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_LazyBaseSpec.inl"
#endif
// semantic
#include "smtc_BaseSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  LazyBaseSpec::LazyBaseSpec (Access access, bool is_virtual, NamePtr const & base_name, gram::BlockVector const & arg_set)
    : BaseSpec (access, is_virtual, base_name), m_arg_set (arg_set)
    {}
}
namespace smtc
{
  LazyBaseSpec::~ LazyBaseSpec ()
    {}
}
namespace smtc
{
  bool LazyBaseSpec::isLazy () const
    {
      return true;
    }
}
#undef LZZ_INLINE
