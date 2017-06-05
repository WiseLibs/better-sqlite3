// smtc_ArgListToString.h
//

#ifndef LZZ_smtc_ArgListToString_h
#define LZZ_smtc_ArgListToString_h
// gram
#include "gram_BlockVector.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String argListToString (gram::BlockVector const & arg_list, int & num_lines);
}
namespace smtc
{
  util::String argListToString (gram::BlockVector const & arg_list);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ArgListToString.inl"
#endif
#endif
