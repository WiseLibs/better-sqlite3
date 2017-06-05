// gram_LexRestOfLine.cpp
//

#include "gram_LexRestOfLine.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_LexRestOfLine.inl"
#endif
// gram
#include "gram_Lexer.h"
#define LZZ_INLINE inline
namespace gram
{
  int lexRestOfLine (Lexer & lexer, util::Loc & eol_loc, basl::TokenVector & token_set)
  {
    int num = 0;
    for (basl::Token token; lexer.getNextToken (eol_loc, token); token_set.push_back (token))
    {
      ++ num;
    }
    return num;
  }
}
#undef LZZ_INLINE
