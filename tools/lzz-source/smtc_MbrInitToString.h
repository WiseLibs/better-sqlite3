// smtc_MbrInitToString.h
//

#ifndef LZZ_smtc_MbrInitToString_h
#define LZZ_smtc_MbrInitToString_h
// semantic
#include "smtc_MbrInitPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String mbrInitToString (MbrInitPtr const & mbr_init);
}
#undef LZZ_INLINE
#endif
