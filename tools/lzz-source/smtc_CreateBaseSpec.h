// smtc_CreateBaseSpec.h
//

#ifndef LZZ_smtc_CreateBaseSpec_h
#define LZZ_smtc_CreateBaseSpec_h
// semantic
#include "smtc_Access.h"
#include "smtc_BaseSpecPtr.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpecPtr createBaseSpec (Access access, bool is_virtual, NamePtr const & base_name);
}
#undef LZZ_INLINE
#endif
