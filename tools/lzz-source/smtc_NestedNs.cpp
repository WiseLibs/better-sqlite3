// smtc_NestedNs.cpp
//

#include "smtc_NestedNs.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NestedNs.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  NestedNs::NestedNs (NsPtr const & encl_ns, util::Loc const & loc)
    : m_encl_ns (encl_ns), m_loc (loc)
    {}
}
namespace smtc
{
  NestedNs::~ NestedNs ()
    {}
}
#undef LZZ_INLINE
