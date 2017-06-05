// gram_RemoveQuotes.cpp
//

#include "gram_RemoveQuotes.h"
// std lib
#include <cstring>
#define LZZ_INLINE inline
namespace gram
{
  util::String removeQuotes (util::Ident const & lexeme)
  {
    char const * str = lexeme.c_str ();
    ++ str;
    return util::String (str, strlen (str) - 1);
  }
}
#undef LZZ_INLINE
