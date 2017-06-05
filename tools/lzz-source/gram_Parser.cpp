// gram_Parser.cpp
//

#include "gram_Parser.h"
// gram
#include "gram_LexPPNumber.h"
#include "gram_ParseRecoverOpt.h"
#include "gram_ParserData.h"
#include "gram_CSPrep.h"
#include "gram_TokenNumber.h"
#include "gram_VisitNode.h"

// semantic
#include "smtc_ScopePtrDeque.h"

// basil
#include "basl_ErrorRec.h"
#include "basl_Lexer.h"
#include "basl_Parse.h"
#include "basl_Parser.h"
#include "basl_SyntaxTree.h"

// config
#include "conf_Config.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  class LzzParser : public basl::Parser
  {
    smtc::ScopePtrDeque ss;
  public:
    LzzParser (smtc::ScopePtr const & scope);
    bool onNode (basl::Nonterm & nonterm);
  };
}
namespace
{
  class LzzLexer : public basl::Lexer
  {
    CSPrep prep;
  public:
    LzzLexer (util::String const & filename, smtc::Output & output);
    LzzLexer (util::String const & str, util::Loc const & loc);
    basl::Token getNextToken (int lex_state);
  };
}
namespace
{
  class LzzPPParser : public basl::Parser
  {
  public:
    LzzPPParser ();
    bool onNode (basl::Nonterm & nonterm);
  };
}
namespace
{
  class LzzPPLexer : public basl::Lexer
  {
    CSPrep prep;
    basl::TokenDeque & token_set;
  public:
    LzzPPLexer (util::String const & filename, basl::TokenDeque & token_set);
    basl::Token getNextToken (int lex_state);
  };
}
namespace
{
  struct InitErrorRec
  {
    basl::ErrorRec error_rec;
    InitErrorRec ();
  };
}
namespace
{
  basl::ErrorRec const & getErrorRec ();
}
namespace
{
  LzzParser::LzzParser (smtc::ScopePtr const & scope)
    {
      ss.push_back (scope);
    }
}
namespace
{
  bool LzzParser::onNode (basl::Nonterm & nonterm)
    {
      visitNode (nonterm, ss);
      return true;
    }
}
namespace
{
  LzzLexer::LzzLexer (util::String const & filename, smtc::Output & output)
    : prep (filename, & output)
    {}
}
namespace
{
  LzzLexer::LzzLexer (util::String const & str, util::Loc const & loc)
    : prep (str, loc)
    {}
}
namespace
{
  basl::Token LzzLexer::getNextToken (int lex_state)
    {
      basl::Token token = prep.getNextToken (lex_state);
      // convert pp-numbers to int and float literals
      if (token.getNumber () == PP_NUMBER_TOKEN)
      {
        lexPPNumber (token);
      }
      return token;
    }
}
namespace
{
  LzzPPParser::LzzPPParser ()
    {}
}
namespace
{
  bool LzzPPParser::onNode (basl::Nonterm & nonterm)
    {
      return true;
    }
}
namespace
{
  LzzPPLexer::LzzPPLexer (util::String const & filename, basl::TokenDeque & token_set)
    : prep (filename, 0), token_set (token_set)
    {}
}
namespace
{
  basl::Token LzzPPLexer::getNextToken (int lex_state)
    {
      basl::Token token = prep.getNextToken (lex_state);
      token_set.push_back (token);
      return token;
    }
}
namespace
{
  InitErrorRec::InitErrorRec ()
    {
      parseRecoverOpt (error_rec);
    }
}
namespace
{
  basl::ErrorRec const & getErrorRec ()
  {
    // initialize error rec only once
    static InitErrorRec init_error_rec;
    return init_error_rec.error_rec;
  }
}
namespace gram
{
  void parse (util::String const & filename, smtc::ScopePtr const & scope, smtc::Output & output)
  {
    LzzLexer lexer (filename, output);
    LzzParser parser (scope);
    bool trace = false;
#ifdef DEBUG_BUILD
    trace = conf::getOptionValue (conf::opt_trace);
#endif
    basl::SyntaxTree tree;
    basl::parse (* getParserData (), lexer, parser, 0, getErrorRec (), trace, tree);
  }
}
namespace gram
{
  basl::SyntaxTree parseString (util::String const & str, util::Loc const & loc, int state, smtc::ScopePtr const & scope)
  {
    LzzLexer lexer (str, loc);
    LzzParser parser (scope);
    bool trace = false;
#ifdef DEBUG_BUILD
    trace = conf::getOptionValue (conf::opt_trace);
#endif
    basl::SyntaxTree tree;
    basl::parse (* getParserData (), lexer, parser, state, getErrorRec (), trace, tree);
    return tree;
  }
}
namespace gram
{
  void ppParse (util::String const & filename, basl::TokenDeque & token_set)
  {
    LzzPPLexer lexer (filename, token_set);
    LzzPPParser parser;
    bool trace = false;
#ifdef DEBUG_BUILD
    trace = conf::getOptionValue (conf::opt_trace);
#endif
    basl::SyntaxTree tree;
    basl::parse (* getParserData (), lexer, parser, 0, getErrorRec (), trace, tree);
  }
}
#undef LZZ_INLINE
