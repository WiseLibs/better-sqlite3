// smtc_AppendCv.h
//

#ifndef LZZ_smtc_AppendCv_h
#define LZZ_smtc_AppendCv_h
// semantic
#include "smtc_Cv.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  void appendCv (util::String & str, bool c, bool v);
}
namespace smtc
{
  void appendCv (util::String & str, Cv const & cv);
}
#undef LZZ_INLINE
#endif
