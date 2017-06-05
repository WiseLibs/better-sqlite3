// smtc_CreateIdentBaseName.cpp
//

#include "smtc_CreateIdentBaseName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_CreateIdentBaseName.inl"
#endif
#include "smtc_IdentBaseName.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseNamePtr createIdentBaseName (util::Loc const & loc, util::Ident const & macro, util::Ident const & ident)
  {
    return new IdentBaseName (loc, macro, ident);
  }
}
#undef LZZ_INLINE
