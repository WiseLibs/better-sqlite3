// smtc_ParamSetToString.h
//

#ifndef LZZ_smtc_ParamSetToString_h
#define LZZ_smtc_ParamSetToString_h
// semantic
#include "smtc_ParamPtrVector.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String paramSetToString (ParamPtrVector const & param_set, bool is_decl);
}
#undef LZZ_INLINE
#endif
