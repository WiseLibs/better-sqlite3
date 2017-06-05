// smtc_CreateNamedNs.h
//

#ifndef LZZ_smtc_CreateNamedNs_h
#define LZZ_smtc_CreateNamedNs_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsPtr createNamedNs (NsPtr const & encl_ns, util::Loc const & loc, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
