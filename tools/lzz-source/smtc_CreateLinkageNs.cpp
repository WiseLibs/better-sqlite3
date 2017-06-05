// smtc_CreateLinkageNs.cpp
//

#include "smtc_CreateLinkageNs.h"
// semantic
#include "smtc_LinkageNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr createLinkageNs (NsPtr const & encl_ns, util::Loc const & loc, util::Ident const & linkage)
  {
    return new LinkageNs (encl_ns, loc, linkage);
  }
}
#undef LZZ_INLINE
