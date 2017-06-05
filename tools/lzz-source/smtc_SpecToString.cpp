// smtc_SpecToString.cpp
//

#include "smtc_SpecToString.h"
// sematnic
#include "smtc_SpecFlags.h"
#define LZZ_INLINE inline
namespace smtc
{
  char const * specToString (int flag)
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
