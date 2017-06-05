// smtc_GetVdfDataId.h
//

#ifndef LZZ_smtc_GetVdfDataId_h
#define LZZ_smtc_GetVdfDataId_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String getVdfDataId (util::String const & vdf_type, util::String const & str);
}
#undef LZZ_INLINE
#endif
