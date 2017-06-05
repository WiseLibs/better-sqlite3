// smtc_LinkageNs.cpp
//

#include "smtc_LinkageNs.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_LinkageNs.inl"
#endif
// semantic
#include "smtc_NsVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  LinkageNs::LinkageNs (NsPtr const & encl_ns, util::Loc const & loc, util::Ident const & linkage)
    : NestedNs (encl_ns, loc), m_linkage (linkage)
    {}
}
namespace smtc
{
  LinkageNs::~ LinkageNs ()
    {}
}
namespace smtc
{
  void LinkageNs::accept (NsVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
