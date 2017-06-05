// smtc_CreateUnnamedNs.cpp
//

#include "smtc_CreateUnnamedNs.h"
// semantic
#include "smtc_UnnamedNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr createUnnamedNs (NsPtr const & encl_ns, util::Loc const & loc)
  {
    return new UnnamedNs (encl_ns, loc);
  }
}
#undef LZZ_INLINE
