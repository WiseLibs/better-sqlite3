// smtc_GetNameLoc.h
//

#ifndef LZZ_smtc_GetNameLoc_h
#define LZZ_smtc_GetNameLoc_h
// semantic
#include "smtc_NamePtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::Loc getNameLoc (smtc::NamePtr const & name);
}
#undef LZZ_INLINE
#endif
