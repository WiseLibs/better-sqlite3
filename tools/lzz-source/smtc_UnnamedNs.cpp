// smtc_UnnamedNs.cpp
//

#include "smtc_UnnamedNs.h"
// semantic
#include "smtc_NsVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  UnnamedNs::UnnamedNs (NsPtr const & encl_ns, util::Loc const & loc)
    : NestedNs (encl_ns, loc)
    {}
}
namespace smtc
{
  UnnamedNs::~ UnnamedNs ()
    {}
}
namespace smtc
{
  void UnnamedNs::accept (NsVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
