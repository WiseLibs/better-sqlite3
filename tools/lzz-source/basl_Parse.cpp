// basl_Parse.cpp
//

#include "basl_Parse.h"
#include "basl_LRBTParser.h"
#define LZZ_INLINE inline
namespace basl
{
  bool parse (LRData const & data, Lexer & lexer, Parser & parser, int start_state, ErrorRec const & error_rec, bool trace, SyntaxTree & tree)
  {
    LRBTParser lrbt_parser (data, lexer, parser, trace);
    return lrbt_parser.parse (start_state, error_rec, tree);
  }
}
#undef LZZ_INLINE
