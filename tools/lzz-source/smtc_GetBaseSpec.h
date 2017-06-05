// smtc_GetBaseSpec.h
//

#ifndef LZZ_smtc_GetBaseSpec_h
#define LZZ_smtc_GetBaseSpec_h
// semantic
#include "smtc_Access.h"
#include "smtc_BaseSpecPtr.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpecPtr getBaseSpec (Access access, bool is_virtual, NamePtr const & base_name);
}
#undef LZZ_INLINE
#endif
