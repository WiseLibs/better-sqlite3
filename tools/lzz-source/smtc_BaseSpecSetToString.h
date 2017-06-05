// smtc_BaseSpecSetToString.h
//

#ifndef LZZ_smtc_BaseSpecSetToString_h
#define LZZ_smtc_BaseSpecSetToString_h
// semantic
#include "smtc_BaseSpecPtrVector.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String baseSpecSetToString (BaseSpecPtrVector const & base_spec_set);
}
#undef LZZ_INLINE
#endif
