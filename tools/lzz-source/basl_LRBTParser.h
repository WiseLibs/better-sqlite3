// basl_LRBTParser.h
//

#ifndef LZZ_basl_LRBTParser_h
#define LZZ_basl_LRBTParser_h
// std lib
#include <deque>

// basil
#include "basl_FreeTokenVector.h"
#include "basl_LRData.h"
#include "basl_RefStack.h"
#include "basl_SyntaxTree.h"
#include "basl_TokenList.h"
#define LZZ_INLINE inline
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
  class Nonterm;
}
namespace basl
{
  class ErrorRec;
}
namespace basl
{
  struct SG
  {
    int state_num;
    int guess_cnt;
    SG (int state_num = 0, int guess_cnt = 0);
  };
}
namespace basl
{
  typedef RefStack <SG> SGStack;
}
namespace basl
{
  struct LRParser
  {
    SGStack sg_stack;
    SyntaxTree tree;
    int guess_cnt;
    TokenListIter token_iter;
    LRParser (int start_state);
  };
}
namespace basl
{
  typedef std::deque <LRParser> LRParserDeque;
}
namespace basl
{
  typedef std::deque <LRParser>::iterator LRParserDequeIter;
}
namespace basl
{
  typedef std::deque <LRParser>::const_iterator LRParserDequeConstIter;
}
namespace basl
{
  struct LRBTParser
  {
    LRData const & data;
    Lexer & lexer;
    Parser & parser;
    bool trace;
  private:
    TokenList token_set;
    bool done;
    int getLexState (LRParser const & lr_parser) const;
    void setNextToken (LRParser & lr_parser);
    TokenListIter getNextToken (TokenListIter token_iter, int lex_state);
    LRActionSeq getActionSeq (LRParser const & lr_parser) const;
    void shift (LRParser & lr_parser, LRAction action, bool guess, bool backtrack);
    bool reduce (LRParser & lr_parser, LRAction action, bool guess, bool backtrack, int & num_cancel);
    bool dfParse (LRParser & lr_parser);
    void bfParse (LRParser & lr_parser, LRParserDeque & lr_parser_set);
  public:
    bool insertSome (LRParser const & start_lr_parser, FreeTokenVector const & free_token_set, LRParser & lr_parser);
    bool discardSome (LRParser const & start_lr_parser, int max_discard, LRParser & lr_parser);
    bool discardOne (LRParser const & start_lr_parser, int number, LRParser & lr_parser);
    bool replaceSome (LRParser const & start_lr_parser, int max_discard, FreeTokenVector const & free_token_set, LRParser & lr_parser);
    bool replaceOne (LRParser const & start_lr_parser, int number, FreeTokenVector const & free_token_set, LRParser & lr_parser);
    bool moveSome (LRParser const & start_lr_parser, int max_move, int max_num, LRParser & lr_parser);
    bool parse (int start_state, ErrorRec const & error_rec, SyntaxTree & tree);
  public:
    explicit LRBTParser (LRData const & data, Lexer & lexer, Parser & parser, bool trace);
    ~ LRBTParser ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_LRBTParser.inl"
#endif
#endif
