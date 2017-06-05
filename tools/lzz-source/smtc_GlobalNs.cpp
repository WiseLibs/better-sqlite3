// smtc_GlobalNs.cpp
//

#include "smtc_GlobalNs.h"
// semantic
#include "smtc_NsVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  GlobalNs::GlobalNs ()
    : Ns ()
    {}
}
namespace smtc
{
  GlobalNs::~ GlobalNs ()
    {}
}
namespace smtc
{
  void GlobalNs::accept (NsVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
