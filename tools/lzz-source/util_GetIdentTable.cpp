// util_GetIdentTable.cpp
//

#include "util_GetIdentTable.h"
#define LZZ_INLINE inline
namespace util
{
  IdentTable & getIdentTable ()
  {
    static IdentTable ident_table;
    return ident_table;
  }
}
#undef LZZ_INLINE
