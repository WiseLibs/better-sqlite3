// smtc_CvTypeSetToString.h
//

#ifndef LZZ_smtc_CvTypeSetToString_h
#define LZZ_smtc_CvTypeSetToString_h
// semantic
#include "smtc_CvTypeVector.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String cvTypeSetToString (CvTypeVector const & cv_type_set);
}
#undef LZZ_INLINE
#endif
