// smtc_ThrowSpecToString.h
//

#ifndef LZZ_smtc_ThrowSpecToString_h
#define LZZ_smtc_ThrowSpecToString_h
// semantic
#include "smtc_ThrowSpecPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String throwSpecToString (ThrowSpecPtr const & throw_spec);
}
#undef LZZ_INLINE
#endif
