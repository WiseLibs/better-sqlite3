// smtc_AccessToString.cpp
//

#include "smtc_AccessToString.h"
// semantic
#define LZZ_INLINE inline
namespace smtc
{
  char const * accessToString (Access access)
  {
    char const * s;
    switch (access)
    {
      case DEFAULT_ACCESS:
      {
        s = "";
        break;
      }
      case PUBLIC_ACCESS:
      {
        s = "public";
        break;
      }
      case PRIVATE_ACCESS:
      {
        s = "private";
        break;
      }
      case PROTECTED_ACCESS:
      {
        s = "protected";
        break;
      }
    }
    return s;
  }
}
#undef LZZ_INLINE
