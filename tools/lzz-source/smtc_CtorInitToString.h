// smtc_CtorInitToString.h
//

#ifndef LZZ_smtc_CtorInitToString_h
#define LZZ_smtc_CtorInitToString_h
// semantic
#include "smtc_CtorInitPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String ctorInitToString (CtorInitPtr const & ctor_init);
}
#undef LZZ_INLINE
#endif
