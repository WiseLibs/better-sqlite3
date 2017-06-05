// smtc_CreateDtorBaseName.cpp
//

#include "smtc_CreateDtorBaseName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_CreateDtorBaseName.inl"
#endif
#include "smtc_DtorBaseName.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseNamePtr createDtorBaseName (util::Loc const & loc, util::Ident const & macro, util::Ident const & ident)
  {
    return new DtorBaseName (loc, macro, ident);
  }
}
#undef LZZ_INLINE
