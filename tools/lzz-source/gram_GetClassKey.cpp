// gram_GetClassKey.cpp
//

#include "gram_GetClassKey.h"
// gram
#include "gram_TokenNumber.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::ClassKey getClassKey (int number)
  {
    smtc::ClassKey key;
    switch (number)
    {
      case CLASS_TOKEN:
      {
        key = smtc::CLASS_KEY;
        break;
      }
      case STRUCT_TOKEN:
      {
        key = smtc::STRUCT_KEY;
        break;
      }
      case UNION_TOKEN:
      {
        key = smtc::UNION_KEY;
        break;
      }
      case ENUM_TOKEN:
      {
        key = smtc::ENUM_KEY;
        break;
      }
      case TYPENAME_TOKEN:
      {
        key = smtc::TYPENAME_KEY;
        break;
      }
    }
    return key;
  }
}
#undef LZZ_INLINE
