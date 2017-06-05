// gram_DiscardRestOfLine.h
//

#ifndef LZZ_gram_DiscardRestOfLine_h
#define LZZ_gram_DiscardRestOfLine_h
// gram
#define LZZ_INLINE inline
namespace gram
{
  class Lexer;
}
namespace gram
{
  void discardRestOfLine (Lexer & lexer);
}
#undef LZZ_INLINE
#endif
