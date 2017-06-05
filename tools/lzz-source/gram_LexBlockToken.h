// gram_LexBlockToken.h
//

#ifndef LZZ_gram_LexBlockToken_h
#define LZZ_gram_LexBlockToken_h
// basil
#include "basl_TokenDeque.h"

#define LZZ_INLINE inline
namespace gram
{
  class Prep;
}
namespace gram
{
  bool lexBlockToken (Prep & prep, int lex_state, basl::Token & token);
}
#undef LZZ_INLINE
#endif
