// smtc_CreateAccessSpec.cpp
//

#include "smtc_CreateAccessSpec.h"
// semantic
#include "smtc_AccessSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  AccessSpecPtr createAccessSpec (util::Loc const & loc, Access access)
  {
    return new AccessSpec (loc, access);
  }
}
#undef LZZ_INLINE
