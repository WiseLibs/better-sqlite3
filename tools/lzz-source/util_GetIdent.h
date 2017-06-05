// util_GetIdent.h
//

#ifndef LZZ_util_GetIdent_h
#define LZZ_util_GetIdent_h
#include "util_Ident.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  util::Ident getIdent (char const * str);
}
namespace util
{
  util::Ident getIdent (util::String const & str);
}
namespace util
{
  util::Ident getIdent (char ch);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "util_GetIdent.inl"
#endif
#endif
