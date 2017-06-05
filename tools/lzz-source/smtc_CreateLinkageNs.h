// smtc_CreateLinkageNs.h
//

#ifndef LZZ_smtc_CreateLinkageNs_h
#define LZZ_smtc_CreateLinkageNs_h
// semantic
#include "smtc_NsPtr.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr createLinkageNs (NsPtr const & encl_ns, util::Loc const & loc, util::Ident const & linkage);
}
#undef LZZ_INLINE
#endif
