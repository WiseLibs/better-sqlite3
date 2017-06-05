// smtc_BaseSpecToString.h
//

#ifndef LZZ_smtc_BaseSpecToString_h
#define LZZ_smtc_BaseSpecToString_h
// semantic
#include "smtc_BaseSpecPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String baseSpecToString (BaseSpecPtr const & base_spec);
}
#undef LZZ_INLINE
#endif
