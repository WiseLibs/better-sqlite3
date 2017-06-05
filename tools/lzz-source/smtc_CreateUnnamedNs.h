// smtc_CreateUnnamedNs.h
//

#ifndef LZZ_smtc_CreateUnnamedNs_h
#define LZZ_smtc_CreateUnnamedNs_h
// semantic
#include "smtc_NsPtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr createUnnamedNs (NsPtr const & encl_ns, util::Loc const & loc);
}
#undef LZZ_INLINE
#endif
