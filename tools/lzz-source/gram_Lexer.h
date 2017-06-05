// gram_Lexer.h
//

#ifndef LZZ_gram_Lexer_h
#define LZZ_gram_Lexer_h
// gram
#include "gram_LineReader.h"

// basil
#include "basl_Token.h"
#define LZZ_INLINE inline
namespace gram
{
  enum LexState
  {
    NORMAL_LEX_STATE = 0,
    INCLUDE_LEX_STATE = 2
  };
}
namespace gram
{
  class Lexer
  {
    LineReader m_reader;
    bool m_from_string;
  public:
    Lexer (util::Filename const & filename);
    Lexer (util::String const & str, util::Loc const & loc);
    bool fromString () const;
    bool fromFile () const;
    bool peekChar (char & ch, int n = 0);
    bool readChar (char & ch);
    void discardRestOfLine ();
    void discardWs ();
    void getRestOfLine (util::String & str);
    bool readLine (util::String & str);
    util::Loc getLoc ();
    bool getNextToken (LexState lex_state, util::Loc & loc, basl::Token & token);
    bool getNextToken (basl::Token & token);
    bool getNextToken (util::Loc & loc, basl::Token & token);
    bool getNextToken (LexState lex_state, basl::Token & token);
    util::Filename const & getFilename () const;
    void setLine (int line);
    void setLine (int line, util::Filename const & filename);
    void pause ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_Lexer.inl"
#endif
#endif
