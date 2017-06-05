// gram_LexRestOfLine.h
//

#ifndef LZZ_gram_LexRestOfLine_h
#define LZZ_gram_LexRestOfLine_h
// gram
#include "basl_TokenVector.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  class Lexer;
}
namespace gram
{
  int lexRestOfLine (Lexer & lexer, util::Loc & eol_loc, basl::TokenVector & token_set);
}
namespace gram
{
  int lexRestOfLine (Lexer & lexer, basl::TokenVector & token_set);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_LexRestOfLine.inl"
#endif
#endif
