// basl_LRBTParser.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE SG::SG (int state_num, int guess_cnt)
    : state_num (state_num), guess_cnt (guess_cnt)
    {}
}
namespace basl
{
  LZZ_INLINE LRParser::LRParser (int start_state)
    : guess_cnt (0)
    {
      sg_stack.push_back (SG (start_state, 0));
    }
}
namespace basl
{
  LZZ_INLINE void LRBTParser::setNextToken (LRParser & lr_parser)
    {
      lr_parser.token_iter = getNextToken (lr_parser.token_iter, getLexState (lr_parser));
    }
}
namespace basl
{
  LZZ_INLINE LRBTParser::LRBTParser (LRData const & data, Lexer & lexer, Parser & parser, bool trace)
    : data (data), lexer (lexer), parser (parser), trace (trace)
         {}
}
#undef LZZ_INLINE
