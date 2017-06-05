// gram_DiscardRestOfLine.cpp
//

#include "gram_DiscardRestOfLine.h"
// gram
#include "gram_Lexer.h"
#define LZZ_INLINE inline
namespace gram
{
  void discardRestOfLine (Lexer & lexer)
  {
    lexer.discardRestOfLine ();
  }
}
#undef LZZ_INLINE
