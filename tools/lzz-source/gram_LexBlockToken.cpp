// gram_LexBlockToken.cpp
//

#include "gram_LexBlockToken.h"
// std lib
#include <cassert>

// gram
#include "gram_BlockTable.h"
#include "gram_CharBlock.h"
#include "gram_Lexer.h"
#include "gram_Message.h"
#include "gram_Prep.h"
#include "gram_TokenBlock.h"
#include "gram_TokenNumber.h"

// config
#include "conf_Config.h"

// util
#include "util_Exception.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct LexBlock
  {
    Prep & prep;
    virtual bool isEndToken (int number) = 0;
    bool tokenLex (basl::Token & res_token);
    bool charLex (basl::Token & res_token);
    bool lex (basl::Token & res_token, bool charlex = false);
  public:
    explicit LexBlock (Prep & prep);
    ~ LexBlock ();
  };
}
namespace
{
  struct LexBlock1 : LexBlock
  {
    int expr_nest;
    int tmpl_nest;
    bool isEndToken (int number);
  public:
    explicit LexBlock1 (Prep & prep);
    ~ LexBlock1 ();
  };
}
namespace
{
  struct LexBlock2 : LexBlock
  {
    int lparen;
    int rparen;
    int expr_nest;
    bool isEndToken (int number);
  public:
    explicit LexBlock2 (Prep & prep, int lparen = LPAREN_TOKEN, int rparen = RPAREN_TOKEN);
    ~ LexBlock2 ();
  };
}
namespace
{
  struct LexBlock5 : LexBlock2
  {
  public:
    explicit LexBlock5 (Prep & prep);
    ~ LexBlock5 ();
  };
}
namespace
{
  struct LexBlock7 : LexBlock2
  {
  public:
    explicit LexBlock7 (Prep & prep);
    ~ LexBlock7 ();
  };
}
namespace
{
  struct LexBlock4 : LexBlock
  {
    int expr_nest;
    bool isEndToken (int number);
  public:
    explicit LexBlock4 (Prep & prep);
    ~ LexBlock4 ();
  };
}
namespace
{
  struct LexBlock3 : LexBlock
  {
    int brac_nest;
    int expr_nest;
    bool isEndToken (int number);
  public:
    explicit LexBlock3 (Prep & prep);
    ~ LexBlock3 ();
  };
}
namespace
{
  struct LexBlock8 : LexBlock
  {
    int gt;
    int expr_nest;
    bool isEndToken (int number);
  public:
    explicit LexBlock8 (Prep & prep, int gt = GT_TOKEN);
    ~ LexBlock8 ();
  };
}
namespace
{
  struct LexBlock9 : LexBlock8
  {
  public:
    explicit LexBlock9 (Prep & prep);
    ~ LexBlock9 ();
  };
}
namespace
{
  struct LexBlock10 : LexBlock
  {
    bool isEndToken (int number);
  public:
    explicit LexBlock10 (Prep & prep);
    ~ LexBlock10 ();
  };
}
namespace gram
{
  bool lexBlockToken (Prep & prep, int lex_state, basl::Token & token)
  {
    bool found = false;
    switch (lex_state)
    {
      // template args
      case 1:
      {
        found = LexBlock1 (prep).lex (token);
        break;
      }
      // parenthesized expr
      case 2:
      {
        found = LexBlock2 (prep).lex (token);
        break;
      }
      // copy and brace init expr
      case 3:
      {
        found = LexBlock3 (prep).lex (token);
        break;
      }
      // direct init expr or func default arg
      case 4:
      {
        found = LexBlock4 (prep).lex (token);
        break;
      }
      // array dimension
      case 5:
      {
        found = LexBlock5 (prep).lex (token);
        break;
      }
      // func body
      case 7:
      {
        found = LexBlock7 (prep).lex (token);
        break;
      }
      // tmpl param default arg 
      case 8:
      {
        found = LexBlock8 (prep).lex (token);
        break;
      }
      // enumerator init
      case 9:
      {
        found = LexBlock9 (prep).lex (token);
        break;
      }
      // return stmt (in navigators)
      case 10:
      {
        found = LexBlock10 (prep).lex (token);
        break;
      }
      default:
      {
        assert (false);
      }
    }
    return found;
  }
}
namespace
{
  bool LexBlock::tokenLex (basl::Token & res_token)
    {
      bool found = false;
      // goto real mode
      prep.setRealMode (true);
      basl::Token next = prep.getNextToken ();
      if (! isEndToken (next.getNumber ()))
      {
        util::Loc start_loc = next.getLoc (); 
        TokenBlock block (start_loc);
        do
        {
          block.append (next);
          next = prep.getNextToken ();
          // watch out for EOT token
          if (next.getNumber () == EOT)
          {
            if (prep.fromFile ())
            {
              msg::eofInCodeBlock (start_loc);
              throw util::Exception ();
            }
            break;
          }
        }
        while (! isEndToken (next.getNumber ()));
        util::Ident lexeme = addBlock (block);
        res_token = basl::Token (BLOCK_TOKEN, start_loc, lexeme);
        found = true;
      }
      // need to unget the end token as it's not part of the block
      prep.ungetToken (next);
      // back to lzz mode
      prep.setRealMode (false);
      return found;
    }
}
namespace
{
  bool LexBlock::charLex (basl::Token & res_token)
    {
      using namespace util;
      bool found = false;
      basl::TokenDeque & token_set = prep.getPendingTokens ();
      Lexer & lexer = prep.getLexer ();
      Loc start_loc = token_set.empty () ? lexer.getLoc () : token_set.front ().getLoc ();
      CharBlock block (start_loc);
      bool found_end = false;
      // first use tokens
      if (! token_set.empty ())
      {
        while (! (token_set.empty () || found_end))
        {
          // check if terminating token
          basl::Token const & token = token_set.front ();
          if (isEndToken (token.getNumber ()))
          {
            found_end = true;
          }
          else
          {
            // otherwise append lexeme and pop token
            block.append (' ');
            block.append (token.getLexeme ().c_str ());
            token_set.pop_front ();
            // found something
            found = true;
          }
        }
        block.append (' ');
      }
      // read from lexer if block not found end
      while (! found_end)
      {
        char ch;
        // should not find end of file
        if (! lexer.peekChar (ch))
        {
          // error if lexing from file 
          if (lexer.fromFile ())
          {
            msg::eofInCodeBlock (start_loc);
            throw Exception ();
          }
          // otherwise lexing BLOCK so must have found end
          found_end = true;
          break;
        }
        // check if start of comment
        char next_ch;
        if (ch == '/' && lexer.peekChar (next_ch, 1) && (next_ch == '*' || next_ch == '/'))
        {
          // save start of comment loc
          util::Loc loc = lexer.getLoc ();
          // read and append '/'
          lexer.readChar (ch);
          block.append (ch);
          // read and append second character
          lexer.readChar (ch);
          block.append (ch);
          if (ch == '*')
          {
            // c-comment
            for (;;)
            {
              // should not be end of file
              if (! lexer.readChar (ch))
              {
                msg::eofInCComment (loc);
                throw Exception ();
              }
              block.append (ch);
              if (ch == '*' && lexer.peekChar (next_ch) && next_ch == '/')
              {
                // read and append '/'
                lexer.readChar (ch);
                block.append (ch);
                break;
              }
            }
          }
          else
          {
            // cpp comment
            do
            {
              lexer.readChar (ch);
              block.append (ch);
            }
            while (ch != '\n');
          }
        }
        // check if start of char literal
        else if (ch == '\'')
        {
          // save start of literal
          util::Loc loc = lexer.getLoc ();
          // read and append quote
          lexer.readChar (ch);
          block.append (ch);
          // next character must not be a quote
          if (lexer.peekChar (ch) && ch == '\'')
          {
            msg::emptyLiteralChar (loc);
            throw Exception ();
          }
          for (bool esc = false;;)
          {
            lexer.readChar (ch);
            if (ch == '\n')
            {
              msg::newlineInLiteralChar (loc);
              throw Exception ();
            }
            block.append (ch);
            if (esc)
            {
              esc = false;
            }
            else if (ch == '\'')
            {
              break;
            }
            else if (ch == '\\')
            {
              esc = true;
            }
          }
          // found something
          found = true;
        }
        // check if start of string literal
        else if (ch == '\"')
        {
          // save start of literal
          util::Loc loc = lexer.getLoc ();
          // read and append quote
          lexer.readChar (ch);
          block.append (ch);
          for (bool esc = false;;)
          {
            lexer.readChar (ch);
            if (ch == '\n')
            {
              msg::newlineInLiteralString (loc);
              throw Exception ();
            }
            block.append (ch);
            if (esc)
            {
              esc = false;
            }
            else if (ch == '\"')
            {
              break;
            }
            else if (ch == '\\')
            {
              esc = true;
            }
          }
          // found something
          found = true;
        }
        else
        {
          // check if special character
          int number = 0; 
          switch (ch)
          {
            case '>':
            case '<':
            {
              // make sure the token isn't left or right shift
              if (lexer.peekChar (next_ch, 1) && next_ch == ch)
              {
                lexer.readChar (ch);
                block.append (ch);
              }
              else
              {
                number = (ch == '<') ? LT_TOKEN : GT_TOKEN;
              }
              break;
            }
            case '(':
            {
              number = LPAREN_TOKEN;
              break;
            }
            case ')':
            {
              number = RPAREN_TOKEN;
              break;
            }
            case '[':
            {
              number = LBRACK_TOKEN;
              break;
            }
            case ']':
            {
              number = RBRACK_TOKEN;
              break;
            }
            case '{':
            {
              number = LBRACE_TOKEN;
              break;
            }
            case '}':
            {
              number = RBRACE_TOKEN;
              break;
            }
            case ';':
            {
              number = SEMI_TOKEN;
              break;
            }
            case ',':
            {
              number = COMMA_TOKEN;
              break;
            }
          }
          if (number > 0 && isEndToken (number))
          {
            // found end of block
            found_end = true;
          }
          else
          {
            // read and append char
            lexer.readChar (ch);
            block.append (ch);
            // found something if ch not space or newline
            if (! (ch == ' ' || ch == '\n'))
            {
              found = true;
            }
          }
        }
      }
      if (found)
      {
        // free unused memory in block then add to table
        block.freeze ();
        util::Ident lexeme = addBlock (block);
        res_token = basl::Token (BLOCK_TOKEN, start_loc, lexeme);
      }
      return found;
    }
}
namespace
{
  bool LexBlock::lex (basl::Token & res_token, bool charlex)
    {
      // are we preprocessing the block?
      bool found = false;
      if (! charlex && conf::getOptionValue (conf::opt_prep_block))
      {
        found = tokenLex (res_token);
      }
      else
      {
        found = charLex (res_token);
      }
      return found;
    }
}
namespace
{
  LZZ_INLINE LexBlock::LexBlock (Prep & prep)
    : prep (prep)
         {}
}
namespace
{
  LexBlock::~ LexBlock ()
         {}
}
namespace
{
  bool LexBlock1::isEndToken (int number)
    {
      bool result = false;
      if (tmpl_nest == 0 && expr_nest == 0 && number == GT_TOKEN)
      {
        result = true;
      }
      else if (number == LPAREN_TOKEN)
      {
        ++ expr_nest;
      }
      else if (number == RPAREN_TOKEN)
      {
        -- expr_nest;
      }
      else if (expr_nest == 0)
      {
        if (number == LT_TOKEN)
        {
          ++ tmpl_nest;
        }
        else if (number == GT_TOKEN)
        {
          -- tmpl_nest;
        }
      }
      return result;
    }
}
namespace
{
  LZZ_INLINE LexBlock1::LexBlock1 (Prep & prep)
    : LexBlock (prep), expr_nest (0), tmpl_nest (0)
         {}
}
namespace
{
  LexBlock1::~ LexBlock1 ()
         {}
}
namespace
{
  bool LexBlock2::isEndToken (int number)
    {
      bool result = false;
      if (expr_nest == 0 && number == rparen)
      {
        result = true;
      }
      else if (number == lparen)
      {
        ++ expr_nest;
      }
      else if (number == rparen)
      {
        -- expr_nest;
      }
      return result;
    }
}
namespace
{
  LZZ_INLINE LexBlock2::LexBlock2 (Prep & prep, int lparen, int rparen)
    : LexBlock (prep), lparen (lparen), rparen (rparen), expr_nest (0)
         {}
}
namespace
{
  LexBlock2::~ LexBlock2 ()
         {}
}
namespace
{
  LZZ_INLINE LexBlock5::LexBlock5 (Prep & prep)
    : LexBlock2 (prep, LBRACK_TOKEN, RBRACK_TOKEN)
         {}
}
namespace
{
  LexBlock5::~ LexBlock5 ()
         {}
}
namespace
{
  LZZ_INLINE LexBlock7::LexBlock7 (Prep & prep)
    : LexBlock2 (prep, LBRACE_TOKEN, RBRACE_TOKEN)
         {}
}
namespace
{
  LexBlock7::~ LexBlock7 ()
         {}
}
namespace
{
  bool LexBlock4::isEndToken (int number)
    {
      bool result = false;
      // in functor def arg may end with ';'
      if (expr_nest == 0 && (number == RPAREN_TOKEN || number == COMMA_TOKEN || number == SEMI_TOKEN))
      {
        result = true;
      }
      else if (number == LPAREN_TOKEN)
      {
        ++ expr_nest;
      }
      else if (number == RPAREN_TOKEN)
      {
        -- expr_nest;
      }
      return result;
    }
}
namespace
{
  LZZ_INLINE LexBlock4::LexBlock4 (Prep & prep)
    : LexBlock (prep), expr_nest (0)
         {}
}
namespace
{
  LexBlock4::~ LexBlock4 ()
         {}
}
namespace
{
  bool LexBlock3::isEndToken (int number)
    {
      bool result = false;
      if ((brac_nest == 0 && expr_nest == 0 && number == COMMA_TOKEN) || number == SEMI_TOKEN)
      {
        result = true;
      }
      else if (number == LBRACE_TOKEN)
      {
        ++ brac_nest;
        expr_nest = 0;
      }
      else if (number == RBRACE_TOKEN && brac_nest > 0)
      {
        -- brac_nest;
      }
      else if (brac_nest == 0)
      {
        if (number == LPAREN_TOKEN)
        {
          ++ expr_nest;
        }
        else if (number == RPAREN_TOKEN && expr_nest > 0)
        {
          -- expr_nest;
        }
      }
      return result;
    }
}
namespace
{
  LZZ_INLINE LexBlock3::LexBlock3 (Prep & prep)
    : LexBlock (prep), brac_nest (0), expr_nest (0)
         {}
}
namespace
{
  LexBlock3::~ LexBlock3 ()
         {}
}
namespace
{
  bool LexBlock8::isEndToken (int number)
    {
      bool result = false;
      if (expr_nest == 0 && (number == gt || number == COMMA_TOKEN))
      {
        result = true;
      }
      else if (number == LPAREN_TOKEN)
      {
        ++ expr_nest;
      }
      else if (number == RPAREN_TOKEN && expr_nest > 0)
      {
        -- expr_nest;
      }
      return result;
    }
}
namespace
{
  LZZ_INLINE LexBlock8::LexBlock8 (Prep & prep, int gt)
    : LexBlock (prep), gt (gt), expr_nest (0)
         {}
}
namespace
{
  LexBlock8::~ LexBlock8 ()
         {}
}
namespace
{
  LZZ_INLINE LexBlock9::LexBlock9 (Prep & prep)
    : LexBlock8 (prep, RBRACE_TOKEN)
         {}
}
namespace
{
  LexBlock9::~ LexBlock9 ()
         {}
}
namespace
{
  bool LexBlock10::isEndToken (int number)
    {
      bool result = false;
      // just capture until next semi
      if (number == SEMI_TOKEN)
      {
        result = true;
      }
      return result;
    }
}
namespace
{
  LZZ_INLINE LexBlock10::LexBlock10 (Prep & prep)
    : LexBlock (prep)
         {}
}
namespace
{
  LexBlock10::~ LexBlock10 ()
         {}
}
#undef LZZ_INLINE
