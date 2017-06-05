// gram_PrintPPTokenSet.h
//

#ifndef LZZ_gram_PrintPPTokenSet_h
#define LZZ_gram_PrintPPTokenSet_h
// std lib
#include <iostream>

// gram
#include "basl_TokenDeque.h"
#define LZZ_INLINE inline
namespace gram
{
  void printPPTokenSet (std::ostream & os, basl::TokenDeque const & token_set);
}
#undef LZZ_INLINE
#endif
