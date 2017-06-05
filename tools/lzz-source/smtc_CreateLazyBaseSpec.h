// smtc_CreateLazyBaseSpec.h
//

#ifndef LZZ_smtc_CreateLazyBaseSpec_h
#define LZZ_smtc_CreateLazyBaseSpec_h
// semantic
#include "smtc_Access.h"
#include "smtc_BaseSpecPtr.h"
#include "smtc_NamePtr.h"

// gram
#include "gram_BlockVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseSpecPtr createLazyBaseSpec (Access access, bool is_virtual, NamePtr const & base_name, gram::BlockVector const & arg_set);
}
#undef LZZ_INLINE
#endif
