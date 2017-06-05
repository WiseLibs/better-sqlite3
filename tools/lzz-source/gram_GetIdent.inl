// gram_GetIdent.inl
//

// gram
#include "util_GetIdent.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE util::Ident getIdent (char const * str)
  {
    return util::getIdent (str);
  }
}
namespace gram
{
  LZZ_INLINE util::Ident getIdent (util::String const & str)
  {
    return util::getIdent (str.c_str ());
  }
}
namespace gram
{
  LZZ_INLINE util::Ident getIdent (char ch)
  {
    return util::getIdent (ch);
  }
}
#undef LZZ_INLINE
