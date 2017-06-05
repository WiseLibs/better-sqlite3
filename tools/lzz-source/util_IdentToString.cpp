// util_IdentToString.cpp
//

#include "util_IdentToString.h"
#define LZZ_INLINE inline
namespace util
{
  String identToString (Ident const & ident)
  {
    return ident.c_str ();
  }
}
#undef LZZ_INLINE
