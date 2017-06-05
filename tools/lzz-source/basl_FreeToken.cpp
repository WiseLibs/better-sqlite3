// basl_FreeToken.cpp
//

#include "basl_FreeToken.h"
#define LZZ_INLINE inline
namespace basl
{
  FreeToken::FreeToken (int number, util::Ident const & lexeme)
    : number (number), lexeme (lexeme)
    {}
}
#undef LZZ_INLINE
