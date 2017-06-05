// util_LocToString.cpp
//

#include "util_LocToString.h"
#define LZZ_INLINE inline
namespace util
{
  String locToString (Loc const & loc)
  {
    String str = loc.getFilename ().getName ();
    char buf [128];
    sprintf (buf, ":%d:%d: ", loc.getLine (), loc.getColumn ());
    str += buf;
    return str;
  }
}
#undef LZZ_INLINE
