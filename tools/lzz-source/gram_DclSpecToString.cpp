// gram_DclSpecToString.cpp
//

#include "gram_DclSpecToString.h"
// gram
#include "gram_DclSpecFlags.h"
#define LZZ_INLINE inline
namespace gram
{
  char const * dclSpecToString (int flag)
  {
    char const * str = 0;
    switch (flag)
    {
      case INLINE_SPEC:
      {
        str = "inline";
        break;
      }
      case VIRTUAL_SPEC:
      {
        str = "virtual";
        break;
      }
      case EXPLICIT_SPEC:
      {
        str = "explicit";
        break;
      }
      case STATIC_SPEC:
      {
        str = "static";
        break;
      }
      case EXTERN_SPEC:
      {
        str = "extern";
        break;
      }
      case MUTABLE_SPEC:
      {
        str = "mutable";
        break;
      }
      case AUTO_SPEC:
      {
        str = "auto";
        break;
      }
      case REGISTER_SPEC:
      {
        str = "register";
        break;
      }
      case PURE_SPEC:
      {
        str = "pure";
        break;
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
