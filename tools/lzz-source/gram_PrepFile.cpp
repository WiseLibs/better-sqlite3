// gram_PrepFile.cpp
//

#include "gram_PrepFile.h"
// gram
#include "gram_Prep.h"
#include "gram_TokenNumber.h"
#define LZZ_INLINE inline
namespace gram
{
  void prepFile (util::String const & filename, bool insert_all, basl::TokenDeque & token_set)
  {
    // no output
    Prep prep (filename, 0, insert_all);
    for (;;)
    {
      // preprocess all tokens, no blocks
      basl::Token token = prep.getNextToken ();
      token_set.push_back (token);
      if (token.getNumber () == EOT)
      {
        break;
      }
    }
  }
}
#undef LZZ_INLINE
