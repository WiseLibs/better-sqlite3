// smtc_NameToString.h
//

#ifndef LZZ_smtc_NameToString_h
#define LZZ_smtc_NameToString_h
// semantic
#include "smtc_NamePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String nameToString (NamePtr const & name);
}
#undef LZZ_INLINE
#endif
