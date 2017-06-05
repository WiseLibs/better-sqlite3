// gram_RemoveQuotes.h
//

#ifndef LZZ_gram_RemoveQuotes_h
#define LZZ_gram_RemoveQuotes_h
// util
#include "util_String.h"
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace gram
{
  util::String removeQuotes (util::Ident const & lexeme);
}
#undef LZZ_INLINE
#endif
