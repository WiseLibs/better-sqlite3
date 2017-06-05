// gram_Lexer.cpp
//

#include "gram_Lexer.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_Lexer.inl"
#endif
// std lib
#include <cassert>
#include <cstdio>

// gram
#include "gram_GetIdent.h"
#include "gram_MacroTable.h"
#include "gram_Message.h"
#include "gram_OperTable.h"
#include "gram_TokenNumber.h"

// util
#include "util_Exception.h"
#include "util_GetIdentTable.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  enum CharKind
  {
    C_D,
    C_E,
    C_F,
    C_HEX_LETTER,
    C_L,
    C_U,
    C_u,
    C_LETTER,
    C_DIGIT,
    C_PLUS,
    C_MINUS,
    C_TIMES,
    C_DIVIDE,
    C_EQ,
    C_LT,
    C_GT,
    C_BANG,
    C_AMPERSAND,
    C_BAR,
    C_CARET,
    C_PERCENT,
    C_DOT,
    C_SQUOTE,
    C_DQUOTE,
    C_BACKSLASH,
    C_COLON,
    C_HASH,
    C_OP,
    C_WS,
    C_LF,
    C_OTHER,
    C_NAC,
    C_EOF
  };
}
namespace
{
  CharKind (char_index) [] =
  {
    // 0
    C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_WS,
    // 10
    C_LF, C_WS, C_WS, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC,
    // 20
    C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC, C_NAC,
    // 30
    C_NAC, C_NAC, C_WS, C_BANG, C_DQUOTE, C_HASH, C_OP, C_PERCENT, C_AMPERSAND, C_SQUOTE,
    // 40
    C_OP, C_OP, C_TIMES, C_PLUS, C_OP, C_MINUS, C_DOT, C_DIVIDE, C_DIGIT, C_DIGIT,
    // 50
    C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_DIGIT, C_COLON, C_OP,
    // 60
    C_LT, C_EQ, C_GT, C_OP, C_OTHER, C_HEX_LETTER, C_HEX_LETTER, C_HEX_LETTER, C_D, C_E,
    // 70
    C_F, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_L, C_LETTER, C_LETTER, C_LETTER,
    // 80
    C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_U, C_LETTER, C_LETTER, C_LETTER, C_LETTER,
    // 90
    C_LETTER, C_OP, C_BACKSLASH, C_OP, C_CARET, C_LETTER, C_OTHER, C_HEX_LETTER, C_HEX_LETTER, C_HEX_LETTER,
    // 100
    C_D, C_E, C_F, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_L, C_LETTER,
    // 110
    C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_LETTER, C_u, C_LETTER, C_LETTER,
    // 120
    C_LETTER, C_LETTER, C_LETTER, C_OP, C_BAR, C_OP, C_OP, C_NAC,
  };
}
namespace
{
  CharKind peekCharKind (LineReader & reader, int n = 0);
}
namespace
{
  enum State
  {
    S_START,
    S_IDENT,
    S_IDENT_U_CHAR,
    S_IDENT_U_CHAR_HEX_COUNT,
    S_L,
    S_PP_NUMBER,
    S_PP_NUMBER_E,
    S_PP_NUMBER_U_CHAR,
    S_PP_NUMBER_U_CHAR_HEX_COUNT,
    S_DOT,
    S_DOT_DOT,
    S_HASH,
    S_BANG,
    S_OP,
    S_LT,
    S_GT,
    S_PLUS,
    S_MINUS,
    S_ARROW,
    S_BAR,
    S_AMPERSAND,
    S_COLON,
    S_PERCENT,
    S_PERCENT_COLON,
    S_CHAR_BEG,
    S_CHAR,
    S_CHAR_END,
    S_CHAR_ESC,
    S_STRING,
    S_STRING_ESC,
    S_STRING_END,
    S_SYS_FILENAME,
    S_UNKNOWN,
    S_CPP_COMMENT_BODY,
    S_C_COMMENT_BODY,
    S_WS,
    S_COMMENT_BEG,
    S_CPP_COMMENT_BEG,
    S_C_COMMENT_BEG,
    S_C_COMMENT_END
  };
}
namespace
{
  basl::Token createIntToken (int kind, util::Loc const & loc, util::Ident const & lexeme, bool octal_error);
}
namespace
{
  CharKind peekCharKind (LineReader & reader, int n)
  {
    CharKind ch_kind = C_EOF;
    char ch;
    if (reader.peekChar (ch, n))
    {
      ch_kind = (ch >= 0 && ch <= 127) ? char_index [ch] : C_LETTER;
    }
    return ch_kind;
  }
}
namespace
{
  basl::Token createIntToken (int kind, util::Loc const & loc, util::Ident const & lexeme, bool octal_error)
  {
    // found an integer, warn if started off as an octal
    if (octal_error)
    {
      msg::octalHasDigitsBeyondRadix (loc, lexeme);
    }
    return basl::Token (kind, loc, lexeme);
  }
}
namespace gram
{
  Lexer::Lexer (util::Filename const & filename)
    : m_reader (filename), m_from_string (false)
    {}
}
namespace gram
{
  Lexer::Lexer (util::String const & str, util::Loc const & loc)
    : m_reader (str, loc), m_from_string (true)
    {}
}
namespace gram
{
  bool Lexer::fromString () const
    {
      return m_from_string;
    }
}
namespace gram
{
  void Lexer::discardRestOfLine ()
    {
      char ch;
      do
      {
        m_reader.readChar (ch);
      }
      while (ch != '\n');
    }
}
namespace gram
{
  void Lexer::discardWs ()
    {
      while (peekCharKind (m_reader) == C_WS)
      {
        char ch;
        m_reader.readChar (ch);
      }
    }
}
namespace gram
{
  void Lexer::getRestOfLine (util::String & str)
    {
      // should not have eof
      if (! readLine (str))
      {
        assert (false);
      }
    }
}
namespace gram
{
  bool Lexer::readLine (util::String & str)
    {
      bool result = false;
      char ch;
      if (m_reader.readChar (ch))
      {
        result = true;
        while (ch != '\n')
        {
          str += ch;
          m_reader.readChar (ch);
        }
      }
      return result;
    }
}
namespace gram
{
  util::Loc Lexer::getLoc ()
    {
      return m_reader.getLocation ();
    }
}
namespace gram
{
  bool Lexer::getNextToken (LexState lex_state, util::Loc & loc, basl::Token & token)
    {
      util::IdentTable & ident_table = util::getIdentTable ();
      CharKind ch_kind = peekCharKind (m_reader);
      bool found_lf = false;
      bool ws_before = false;
      // remaining hex digits in universal char
      int num_hex_digits = 0;
      for (bool found = false; ! found;)
      {
        loc = m_reader.getLocation ();
        bool found_ws = false;
        int state = S_START;
        for (;;)
        {
          switch (state)
          {
            // start
            case S_START:
            {
              switch (ch_kind)
              {
                // letter
                case C_D:
                case C_E:
                case C_F:
                case C_U:
                case C_u:
                case C_HEX_LETTER:
                case C_LETTER:
                {
                  state = S_IDENT;
                  break;
                }
                // l
                case C_L:
                {
                  state = S_L;
                  break;
                }
                // digit
                case C_DIGIT:
                {
                  state = S_PP_NUMBER;
                  break;
                }
                // dot
                case C_DOT:
                {
                  state = S_DOT;
                  break;
                }
                // '
                case C_SQUOTE:
                {
                  state = S_CHAR_BEG;
                  break;
                }
                // "
                case C_DQUOTE:
                {
                  state = S_STRING;
                  break;
                }
                // op
                case C_OP:
                {
                  state = S_OP;
                  break;
                }
                // #
                case C_HASH:
                {
                  state = S_HASH;
                  break;
                }
                // ! = * ^
                case C_BANG:
                case C_EQ:
                case C_CARET:
                case C_TIMES:
                {
                  state = S_BANG;
                  break;
                }
                // <
                case C_LT:
                {
                  if (lex_state != INCLUDE_LEX_STATE)
                  {
                    state = S_LT;
                  }
                  else
                  {
                    state = S_SYS_FILENAME;
                  }
                  break;
                }
                // >
                case C_GT:
                {
                  state = S_GT;
                  break;
                }
                // +
                case C_PLUS:
                {
                  state = S_PLUS;
                  break;
                }
                // -
                case C_MINUS:
                {
                  state = S_MINUS;
                  break;
                }
                // |
                case C_BAR:
                {
                  state = S_BAR;
                  break;
                }
                // &
                case C_AMPERSAND:
                {
                  state = S_AMPERSAND;
                  break;
                }
                // :
                case C_COLON:
                {
                  state = S_COLON;
                  break;
                }
                // %
                case C_PERCENT:
                {
                  state = S_PERCENT;
                  break;
                }
                // /
                case C_DIVIDE:
                {
                  int next_ch_kind = peekCharKind (m_reader, 1);
                  if (next_ch_kind == C_DIVIDE || next_ch_kind == C_TIMES)
                  {
                    state = S_COMMENT_BEG;
                  }
                  else
                  {
                    state = S_BANG;
                  }
                  break;
                }
                // white space
                case C_WS:
                {
                  state = S_WS;
                  break;
                }
                // backslash
                case C_BACKSLASH:
                {
                  // check if start of universal char
                  int next_ch_kind = peekCharKind (m_reader, 1);
                  if (next_ch_kind == C_U || next_ch_kind == C_u)
                  {
                    state = S_IDENT_U_CHAR;
                  }
                  else
                  {
                    state = S_UNKNOWN;
                  }
                  break;
                }
                // non-whitespace characters not part of other another token
                case C_OTHER:
                {
                  state = S_UNKNOWN;
                  break;
                }
                // eof
                case C_EOF:
                {
                  token = basl::Token (EOT, loc, util::Ident ("end of file"));
                  found = true;
                  break;
                }
                // new line
                case C_LF:
                {
                  // read newline, but don't yet read next char on line! (#line will set wrong line number)
                  char ch;
                  m_reader.readChar (ch);
                  found_lf = true;
                  found = true;
                  break;
                }
                // nac
                case C_NAC:
                {
                  msg::invalidChar (loc);
                  throw util::Exception ();
                }
              }
              break;
            }
            // ident
            case S_IDENT:
            {
              if (ch_kind > C_DIGIT)
              {
                if (ch_kind == C_BACKSLASH)
                {
                  // might be universal char
                  int next_ch_kind = peekCharKind (m_reader, 1);
                  if (next_ch_kind == C_U || next_ch_kind == C_u)
                  {
                    state = S_IDENT_U_CHAR;
                  }
                }
                if (state == S_IDENT)
                {
                  util::Ident lexeme = ident_table.getIdent ();
                  token = basl::Token (isPersistentMacro (lexeme) ? MACRO_TOKEN : IDENT_TOKEN, loc, lexeme);
                  found = true;
                }
              }
              break;
            }
            // universal char in ident
            case S_IDENT_U_CHAR:
            {
              // 4 hex digits if 'u', 8 if 'U'
              num_hex_digits = ch_kind == C_U ? 8 : 4;
              state = S_IDENT_U_CHAR_HEX_COUNT;
              break;
            }
            // counting chars in universal char
            case S_IDENT_U_CHAR_HEX_COUNT:
            {
              if (ch_kind <= C_HEX_LETTER || ch_kind == C_DIGIT)
              {
                if (-- num_hex_digits == 0)
                {
                  state = S_IDENT; 
                }
              }
              else
              {
                // insufficent hex digits
                msg::invalidUniversalChar (loc);
                // create identifier anyway or continue lexing identifier
                if (ch_kind > C_DIGIT)
                {
                  util::Ident lexeme = ident_table.getIdent ();
                  token = basl::Token (isPersistentMacro (lexeme) ? MACRO_TOKEN : IDENT_TOKEN, loc, lexeme);
                  found = true;
                }
                else
                {
                  state = S_IDENT;
                }
              }
              break;
            }
            // l
            case S_L:
            {
              if (ch_kind == C_SQUOTE)
              {
                state = S_CHAR_BEG;
              }
              // can't have 'L' prefix with header file
              else if (ch_kind == C_DQUOTE && lex_state != INCLUDE_LEX_STATE)
              {
                state = S_STRING;
              }
              else if (ch_kind <= C_DIGIT)
              {
                state = S_IDENT;
              }
              else
              {
                util::Ident lexeme = ident_table.getIdent ();
                token = basl::Token (isPersistentMacro (lexeme) ? MACRO_TOKEN : IDENT_TOKEN, loc, lexeme);
                found = true;
              }
              break;
            }
            // pp number
            case S_PP_NUMBER:
            {
              if (ch_kind == C_E)
              {
                state = S_PP_NUMBER_E;
              }
              else if (ch_kind > C_DIGIT && ch_kind != C_DOT)
              {
                if (ch_kind == C_BACKSLASH)
                {
                  // might be universal char
                  int next_ch_kind = peekCharKind (m_reader, 1);
                  if (next_ch_kind == C_U || next_ch_kind == C_u)
                  {
                    state = S_PP_NUMBER_U_CHAR;
                  }
                }
                if (state == S_PP_NUMBER)
                {
                  // not a non digit, digit nor start of universal char
                  token = basl::Token (PP_NUMBER_TOKEN, loc, ident_table.getIdent ());
                  found = true;
                }
              }
              break;
            }
            // pp number followed by E or e
            case S_PP_NUMBER_E:
            {
              if (ch_kind == C_E)
              {
                // stay in same state
              }
              else if (ch_kind <= C_MINUS || ch_kind == C_DOT)
              {
                // non digit, digit, sign or dot
                state = S_PP_NUMBER;
              }
              else
              {
                token = basl::Token (PP_NUMBER_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // universal char in pp number
            case S_PP_NUMBER_U_CHAR:
            {
              // 4 hex digits if 'u', 8 if 'U'
              num_hex_digits = ch_kind == C_U ? 8 : 4;
              state = S_PP_NUMBER_U_CHAR_HEX_COUNT;
              break;
            }
            // counting chars in universal char
            case S_PP_NUMBER_U_CHAR_HEX_COUNT:
            {
              if (ch_kind <= C_HEX_LETTER || ch_kind == C_DIGIT)
              {
                // hex letter or digit
                if (-- num_hex_digits == 0)
                {
                  state = S_PP_NUMBER; 
                }
              }
              else
              {
                // insufficent hex digits
                msg::invalidUniversalChar (loc);
                // try to continue lexing pp number or create a pp number token
                if (ch_kind == C_E)
                {
                  state = S_PP_NUMBER_E;
                }
                else if (ch_kind <= C_DIGIT || ch_kind == C_DOT)
                {
                  // digit, non digit or dot
                  state = S_PP_NUMBER;
                }
                else
                {
                  token = basl::Token (PP_NUMBER_TOKEN, loc, ident_table.getIdent ());
                  found = true;
                }
              }
              break;
            }
            // dot
            case S_DOT:
            {
              if (ch_kind == C_DIGIT)
              {
                state = S_PP_NUMBER;
              }
              else if (ch_kind == C_DOT && peekCharKind (m_reader, 1) == C_DOT)
              {
                state = S_DOT_DOT;
              }
              else if (ch_kind == C_TIMES)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (DOT_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // .. next . or %:% next :
            case S_DOT_DOT:
            {
              state = S_OP;
              break;
            }
            // #
            case S_HASH:
            {
              if (ch_kind == C_HASH)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (HASH_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // ! = * ^ /
            case S_BANG:
            {
              if (ch_kind == C_EQ)
              {
                state = S_OP;
              }
              else
              {
                util::Ident lexeme = ident_table.getIdent ();
                token = basl::Token (getOperKind (lexeme), loc, lexeme);
                found = true;
              }
              break;
            }
            // op
            case S_OP:
            {
              util::Ident lexeme = ident_table.getIdent ();
              token = basl::Token (getOperKind (lexeme), loc, lexeme);
              found = true;
              break;
            }
            // <
            case S_LT:
            {
              if (ch_kind == C_LT)
              {
                state = S_BANG;
              }
              else if (ch_kind == C_EQ || ch_kind == C_COLON || ch_kind == C_PERCENT)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (LT_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // >
            case S_GT:
            {
              if (ch_kind == C_GT)
              {
                state = S_BANG;
              }
              else if (ch_kind == C_EQ)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (GT_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // +
            case S_PLUS:
            {
              if (ch_kind == C_PLUS || ch_kind == C_EQ)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (PLUS_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // -
            case S_MINUS:
            {
              if (ch_kind == C_MINUS || ch_kind == C_EQ)
              {
                state = S_OP;
              }
              else if (ch_kind == C_GT)
              {
                state = S_ARROW;
              }
              else
              {
                token = basl::Token (MINUS_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // ->
            case S_ARROW:
            {
              if (ch_kind == C_TIMES)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (PTR_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // |
            case S_BAR:
            {
              if (ch_kind == C_BAR || ch_kind == C_EQ)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (BITOR_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // &
            case S_AMPERSAND:
            {
              if (ch_kind == C_AMPERSAND || ch_kind == C_EQ)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (BITAND_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // :
            case S_COLON:
            {
              if (ch_kind == C_COLON || ch_kind == C_GT)
              {
                state = S_OP;
              }
              else
              {
                token = basl::Token (COLON_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // %
            case S_PERCENT:
            {
              if (ch_kind == C_GT || ch_kind == C_EQ)
              {
                state = S_OP;
              }
              else if (ch_kind == C_COLON)
              {
                state = S_PERCENT_COLON;
              }
              else
              {
                token = basl::Token (MOD_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // %:
            case S_PERCENT_COLON:
            {
              if (ch_kind == C_PERCENT && peekCharKind (m_reader, 1) == C_COLON)
              {
                state = S_DOT_DOT; 
              }
              else
              {
                token = basl::Token (HASH_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              break;
            }
            // char beg
            case S_CHAR_BEG:
            {
              if (ch_kind == C_SQUOTE)
              {
                msg::emptyLiteralChar (loc);
                // assume ' ' 
                ident_table.push (' ');
                state = S_CHAR_END;
              }
              else if (ch_kind == C_LF)
              {
                msg::newlineInLiteralChar (loc);
                // assume ' '
                ident_table.push (' ');
                ident_table.push ('\'');
                token = basl::Token (LITERAL_CHAR_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              else if (ch_kind == C_BACKSLASH)
              {
                state = S_CHAR_ESC; 
              }
              else
              {
                state = S_CHAR;
              }
              break;
            }
            // char
            case S_CHAR:
            {
              if (ch_kind == C_LF)
              {
                msg::newlineInLiteralChar (loc);
                // add missing end quote 
                ident_table.push ('\'');
                token = basl::Token (LITERAL_CHAR_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              else if (ch_kind == C_BACKSLASH)
              {
                state = S_CHAR_ESC;
              }
              else if (ch_kind == C_SQUOTE)
              {
                state = S_CHAR_END;
              }
              break;
            }
            // char escape
            case S_CHAR_ESC:
            {
              // can't be newline
              // accept any other character
              state = S_CHAR;
              break;
            }
            // char end
            case S_CHAR_END:
            {
              token = basl::Token (LITERAL_CHAR_TOKEN, loc, ident_table.getIdent ());
              found = true;
              break;
            }
            // string
            case S_STRING:
            {
              if (ch_kind == C_LF)
              {
                msg::newlineInLiteralString (loc);
                // add mising end quote
                ident_table.push ('\"');
                util::Ident lexeme = ident_table.getIdent ();
                int kind = LITERAL_STRING_TOKEN;
                token = basl::Token (kind, loc, lexeme);
                found = true;
              }
              else if (ch_kind == C_BACKSLASH)
              {
                state = S_STRING_ESC;
              }
              else if (ch_kind == C_DQUOTE)
              {
                state = S_STRING_END;
              }
              else
              {
                state = S_STRING;
              }
              break;
            }
            // string escape
            case S_STRING_ESC:
            {
              // can't be newline
              // accept any other character
              state = S_STRING;
              break;
            }
            // string end
            case S_STRING_END:
            {
              util::Ident lexeme = ident_table.getIdent ();
              int kind = LITERAL_STRING_TOKEN;
              token = basl::Token (kind, loc, lexeme);
              found = true;
              break;
            }
            // system filename
            case S_SYS_FILENAME:
            {
              if (ch_kind == C_LF)
              {
                msg::newlineInLiteralString (loc);
                // add end '>'
                ident_table.push ('>');
                token = basl::Token (LITERAL_STRING_TOKEN, loc, ident_table.getIdent ());
                found = true;
              }
              else if (ch_kind == C_GT)
              {
                state = S_STRING_END;
              }
              break;
            }
            // unknown
            case S_UNKNOWN:
            {
              token = basl::Token (UNKNOWN_TOKEN, loc, ident_table.getIdent ());
              found = true;
              break;
            }
            // / next * or /
            case S_COMMENT_BEG:
            {
              if (ch_kind == C_TIMES)
              {
                state = S_C_COMMENT_BEG;
              }
              else
              {
                state = S_CPP_COMMENT_BEG;
              }
              break;
            }
            // /* ...
            case S_C_COMMENT_BEG:
            {
              state = S_C_COMMENT_BODY;
              // fall through 
            }
            case S_C_COMMENT_BODY:
            {
              if (ch_kind == C_EOF)
              {
                msg::eofInCComment (loc);
                // assume end
                found_ws = true;
              }
              else if (ch_kind == C_TIMES && peekCharKind (m_reader, 1) == C_DIVIDE)
              {
                state = S_C_COMMENT_END;
              }
              break;
            }
            // /* ... * next /
            case S_C_COMMENT_END:
            {
              state = S_WS;
              break;
            }
            // // ...
            case S_CPP_COMMENT_BEG:
            {
              state = S_CPP_COMMENT_BODY;
              // fall through
            }
            case S_CPP_COMMENT_BODY:
            {
              if (ch_kind == C_LF)
              {
                found_ws = true;
              }
              break;
            }
            // white space
            case S_WS:
            {
              if (ch_kind != C_WS)
              {
                found_ws = true;
              }
              break;
            }
          }
          // break if found token (or newline) or whitespace
          if (found)
          {
            break;
          }
          if (found_ws)
          {
            ws_before = true;
            break;
          }
          // get next char
          char ch;
          m_reader.readChar (ch);
          if (state <= S_UNKNOWN)
          {
            // push ident char
            ident_table.push (ch);
          }
          ch_kind = peekCharKind (m_reader);
        }
      }
      if (found_lf)
      {
        return false;
      }
      if (ws_before)
      {
        token.setSpaceBefore ();
      }
      return true;
    }
}
#undef LZZ_INLINE
