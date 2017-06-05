// gram_PrintPPTokenSet.cpp
//

#include "gram_PrintPPTokenSet.h"
// gram
#include "gram_PrettyPrintTokens.h"
#define LZZ_INLINE inline
namespace gram
{
  void printPPTokenSet (std::ostream & os, basl::TokenDeque const & token_set)
  {
    prettyPrintTokensToStream (os, token_set);

    /*
    std::for_each (token_set.begin (), token_set.end (), PrintPPToken (os));
    // print final newline if token_set not complete
    if (token_set.back ().getNumber () != EOT)
    {
      os << '\n';
    }
    */
  }
}
#undef LZZ_INLINE
