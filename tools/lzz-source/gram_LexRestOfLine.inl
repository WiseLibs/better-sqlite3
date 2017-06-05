// gram_LexRestOfLine.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE int lexRestOfLine (Lexer & lexer, basl::TokenVector & token_set)
  {
    util::Loc eol_loc;
    return lexRestOfLine (lexer, eol_loc, token_set);
  }
}
#undef LZZ_INLINE
