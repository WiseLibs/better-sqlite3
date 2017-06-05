// gram_LiteralCharToInt.cpp
//

#include "gram_LiteralCharToInt.h"
// gram
#include "gram_TranslateLiteralChar.h"
#define LZZ_INLINE inline
namespace gram
{
  unsigned int literalCharToInt (util::Loc const & loc, util::Ident const & lexeme)
  {
    char const * str = lexeme.c_str ();
    // skip wide prefix if present
    if (* str == 'l' || * str == 'L')
    {
      ++ str;
    }
    // skip begin quote
    ++ str;
    // convert first char
    return translateLiteralChar (loc, str, & str);
  }
}
#undef LZZ_INLINE
