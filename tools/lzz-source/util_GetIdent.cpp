// util_GetIdent.cpp
//

#include "util_GetIdent.h"
#ifndef LZZ_ENABLE_INLINE
#include "util_GetIdent.inl"
#endif
#include "util_GetIdentTable.h"
#define LZZ_INLINE inline
namespace util
{
  util::Ident getIdent (char const * str)
  {
    return getIdentTable ().getIdent (str);
  }
}
namespace util
{
  util::Ident getIdent (char ch)
  {
    IdentTable & ident_table = getIdentTable ();
    ident_table.push (ch);
    return ident_table.getIdent ();
  }
}
#undef LZZ_INLINE
