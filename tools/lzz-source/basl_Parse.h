// basl_Parse.h
//

#ifndef LZZ_basl_Parse_h
#define LZZ_basl_Parse_h
#define LZZ_INLINE inline
namespace basl
{
  struct LRData;
}
namespace basl
{
  class Lexer;
}
namespace basl
{
  class Parser;
}
namespace basl
{
  class SyntaxTree;
}
namespace basl
{
  class ErrorRec;
}
namespace basl
{
  bool parse (LRData const & data, Lexer & lexer, Parser & parser, int start_state, ErrorRec const & error_rec, bool trace, SyntaxTree & tree);
}
#undef LZZ_INLINE
#endif
