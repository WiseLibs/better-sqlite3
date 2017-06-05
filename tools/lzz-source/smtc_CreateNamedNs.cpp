// smtc_CreateNamedNs.cpp
//

#include "smtc_CreateNamedNs.h"
// semantic
#include "smtc_NamedNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr createNamedNs (NsPtr const & encl_ns, util::Loc const & loc, NamePtr const & name)
  {
    return new NamedNs (encl_ns, loc, name);
  }
}
#undef LZZ_INLINE
