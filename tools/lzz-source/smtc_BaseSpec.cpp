// smtc_BaseSpec.cpp
//

#include "smtc_BaseSpec.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_BaseSpec.inl"
#endif
// semantic
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpec::BaseSpec (Access access, bool is_virtual, NamePtr const & base_name)
    : m_access (access), m_is_virtual (is_virtual), m_base_name (base_name)
    {}
}
namespace smtc
{
  BaseSpec::~ BaseSpec ()
    {}
}
namespace smtc
{
  bool BaseSpec::isLazy () const
    {
      return false;
    }
}
#undef LZZ_INLINE
