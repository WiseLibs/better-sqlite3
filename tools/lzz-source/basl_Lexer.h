// basl_Lexer.h
//

#ifndef LZZ_basl_Lexer_h
#define LZZ_basl_Lexer_h
#define LZZ_INLINE inline
namespace basl
{
  class Token;
}
namespace basl
{
  class Lexer
  {
  public:
    virtual ~ Lexer ();
    virtual Token getNextToken (int lex_state) = 0;
  };
}
#undef LZZ_INLINE
#endif
