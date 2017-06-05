// smtc_ClassKeyToString.cpp
//

#include "smtc_ClassKeyToString.h"
#define LZZ_INLINE inline
namespace smtc
{
  char const * classKeyToString (ClassKey key)
  {
    char const * str;
    switch (key)
    {
      case CLASS_KEY:
      {
        str = "class";
        break;
      }
      case STRUCT_KEY:
      {
        str = "struct";
        break;
      }
      case UNION_KEY:
      {
        str = "union";
        break;
      }
      case ENUM_KEY:
      {
        str = "enum";
        break;
      }
      case TYPENAME_KEY:
      {
        str = "typename";
        break;
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
