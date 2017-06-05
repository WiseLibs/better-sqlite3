// smtc_MbrInitSetToString.h
//

#ifndef LZZ_smtc_MbrInitSetToString_h
#define LZZ_smtc_MbrInitSetToString_h
// semantic
#include "smtc_MbrInitPtrVector.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String mbrInitSetToString (MbrInitPtrVector const & mbr_init_set);
}
#undef LZZ_INLINE
#endif
