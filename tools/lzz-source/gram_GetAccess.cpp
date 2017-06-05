// gram_GetAccess.cpp
//

#include "gram_GetAccess.h"
// gram
#include "gram_TokenNumber.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::Access getAccess (int number)
  {
    smtc::Access access;
    switch (number)
    {
      case PUBLIC_TOKEN:
      {
        access = smtc::PUBLIC_ACCESS;
        break;
      }
      case PROTECTED_TOKEN:
      {
        access = smtc::PROTECTED_ACCESS;
        break;
      }
      case PRIVATE_TOKEN:
      {
        access = smtc::PRIVATE_ACCESS;
        break;
      }
    }
    return access;
  }
}
#undef LZZ_INLINE
