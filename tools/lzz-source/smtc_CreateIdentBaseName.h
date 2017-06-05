// smtc_CreateIdentBaseName.h
//

#ifndef LZZ_smtc_CreateIdentBaseName_h
#define LZZ_smtc_CreateIdentBaseName_h
#include "smtc_BaseNamePtr.h"
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseNamePtr createIdentBaseName (util::Loc const & loc, util::Ident const & ident);
}
namespace smtc
{
  BaseNamePtr createIdentBaseName (util::Loc const & loc, util::Ident const & macro, util::Ident const & ident);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_CreateIdentBaseName.inl"
#endif
#endif
