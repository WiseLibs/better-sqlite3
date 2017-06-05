// smtc_CreateAccessSpec.h
//

#ifndef LZZ_smtc_CreateAccessSpec_h
#define LZZ_smtc_CreateAccessSpec_h
// semantic
#include "smtc_Access.h"
#include "smtc_AccessSpecPtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  AccessSpecPtr createAccessSpec (util::Loc const & loc, Access access);
}
#undef LZZ_INLINE
#endif
