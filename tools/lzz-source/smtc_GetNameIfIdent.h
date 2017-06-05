// smtc_GetNameIfIdent.h
//

#ifndef LZZ_smtc_GetNameIfIdent_h
#define LZZ_smtc_GetNameIfIdent_h
// semantic
#include "smtc_NamePtr.h"

// util
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::Ident getNameIfIdent (NamePtr const & name);
}
#undef LZZ_INLINE
#endif
