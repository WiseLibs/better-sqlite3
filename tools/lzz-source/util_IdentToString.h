// util_IdentToString.h
//

#ifndef LZZ_util_IdentToString_h
#define LZZ_util_IdentToString_h
// util
#include "util_Ident.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  String identToString (Ident const & ident);
}
#undef LZZ_INLINE
#endif
