// smtc_NamedNs.cpp
//

#include "smtc_NamedNs.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NamedNs.inl"
#endif
// semantic
#include "smtc_NsVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamedNs::NamedNs (NsPtr const & encl_ns, util::Loc const & loc, NamePtr const & name)
    : NestedNs (encl_ns, loc), m_name (name)
    {}
}
namespace smtc
{
  NamedNs::~ NamedNs ()
    {}
}
namespace smtc
{
  void NamedNs::accept (NsVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
