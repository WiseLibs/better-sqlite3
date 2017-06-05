// smtc_GetBaseNameIfIdent.h
//

#ifndef LZZ_smtc_GetBaseNameIfIdent_h
#define LZZ_smtc_GetBaseNameIfIdent_h
// semantic
#include "smtc_BaseNamePtr.h"

// util
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::Ident getBaseNameIfIdent (BaseNamePtr const & base_name);
}
#undef LZZ_INLINE
#endif
