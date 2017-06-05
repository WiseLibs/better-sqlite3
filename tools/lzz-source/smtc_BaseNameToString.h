// smtc_BaseNameToString.h
//

#ifndef LZZ_smtc_BaseNameToString_h
#define LZZ_smtc_BaseNameToString_h
// semantic
#include "smtc_BaseNamePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String baseNameToString (BaseNamePtr const & base_name);
}
#undef LZZ_INLINE
#endif
