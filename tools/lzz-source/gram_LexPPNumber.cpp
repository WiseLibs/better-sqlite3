// gram_LexPPNumber.cpp
//

#include "gram_LexPPNumber.h"
// std lib
#include <cassert>

// gram
#include "gram_Message.h"
#include "gram_TokenNumber.h"

// util
#include "util_GetIdentTable.h"
#define LZZ_INLINE inline
namespace
{
  char peekChar (char const * s, int i);
}
namespace
{
  char peekChar (char const * s, int i)
  {
    char ch = * s;
    for (; ch != '\0' && i > 0; -- i)
    {
      ch = * ++ s;
    }
    return ch;
  }
}
namespace gram
{
  void lexPPNumber (basl::Token & token)
  {
    // do nothing if not a pp-number
    if (token.getNumber () != PP_NUMBER_TOKEN)
    {
      return;
    }

    // lex states
    enum
    {
      // start
      S_START,

      // zero
      S_ZERO,

      // zero followed by X
      S_ZERO_X,

      // octal integer
      S_OCTAL_INT,

      // hex integer
      S_HEX_INT,
    
      // integer
      S_INT,

      // integer with l suffix
      S_INT_L_SUFFIX,

      // integer with u suffix
      S_INT_U_SUFFIX,

      // integer with ul suffix
      S_INT_UL_SUFFIX,

      // integer with ll suffix
      S_INT_LL_SUFFIX,

      // integer with i suffix, 64 next 
      S_INT_I_SUFFIX,

      // integer with i6 suffix, 4 next
      S_INT_I6_SUFFIX,

      // integer with ui suffix, 64 next
      S_INT_UI_SUFFIX,

      // integer with ui6 suffix, 4 next
      S_INT_UI6_SUFFIX,

      // integer with suffix
      S_INT_SUFFIX,

      // float
      S_FLOAT,

      // float followed by E
      S_FLOAT_E,

      // float followed by E and sign
      S_FLOAT_E_SIGN,

      // float exponent (number)
      S_FLOAT_EXP,

      // float followed by suffix
      S_FLOAT_SUFFIX,

      // .
      S_DOT
    };

    util::IdentTable & ident_table = util::getIdentTable ();
    util::Loc const & loc = token.getLoc ();
    char const * s = token.getLexeme ().c_str ();
    // true if octal error
    bool octal_error = false;
    int kind = 0;
    // true if message output while lexing
    bool error = false;
    int state = S_START;
    for (;;)
    {
      char ch = * s;
      switch (state)
      {
        // start
        case S_START:
        {
          if (ch == '0')
          {
            state = S_ZERO;
          }
          else if (ch >= '1' && ch <= '9')
          {
            state = S_INT;
          }
          else
          {
            assert (ch == '.');
            state = S_DOT;
          }
          break;
        }
        // zero
        case S_ZERO:
        {
          if (ch == 'x' || ch == 'X')
          {
            state = S_ZERO_X;
          }
          else if (ch == '.')
          {
            state = S_FLOAT;
          }
          else if (ch == 'E' || ch == 'e')
          {
            state = S_FLOAT_E;
          }
          else if (ch == 'L' || ch == 'l')
          {
            state = S_INT_L_SUFFIX;
          }
          else if (ch == 'U' || ch == 'u')
          {
            state = S_INT_U_SUFFIX;
          }
          else if (ch == 'i' && peekChar (s, 1) == '6' && peekChar (s, 2) == '4')
          {
            state = S_INT_I_SUFFIX;
          }
          else if (ch >= '0' && ch <= '7')
          {
            state = S_OCTAL_INT;
          }
          else if (ch >= '8' && ch <= '9')
          {
            // can't be an octal, maybe float
            octal_error = true;
            state = S_INT;
          }
          else
          {
            // this is a *zero* int literal token
            kind = ZERO_TOKEN;
          }
          break;
        }
        // zero followed by x
        case S_ZERO_X:
        {
          if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'f' || ch >= 'A' && ch <= 'F')
          {
            state = S_HEX_INT;
          }
          else
          {
            // missing hex digit, append 0 to make valid
            msg::missingHexDigitsInIntLiteral (loc);
            error = true;
            // try to recover
            ident_table.push ('0');
            if (ch == 'L' || ch == 'l')
            {
              state = S_INT_L_SUFFIX;
            }
            else if (ch == 'U' || ch == 'u')
            {
              state = S_INT_U_SUFFIX;
            }
            else if (ch == 'i' && peekChar (s, 1) == '6' && peekChar (s, 2) == '4')
            {
              state = S_INT_I_SUFFIX;
            }
            else
            {
              kind = LITERAL_INT_TOKEN;
            }
          }
          break;
        }
        // hexadecimal integer
        case S_HEX_INT:
        {
          if (ch == 'L' || ch == 'l')
          {
            state = S_INT_L_SUFFIX;
          }
          else if (ch == 'U' || ch == 'u')
          {
            state = S_INT_U_SUFFIX;
          }
          else if (ch == 'i' && peekChar (s, 1) == '6' && peekChar (s, 2) == '4')
          {
            state = S_INT_I_SUFFIX;
          }
          else if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'f' || ch >= 'A' && ch <= 'F')
          {
            // stay in same state
          }
          else
          {
            kind = LITERAL_INT_TOKEN;
          }
          break;
        }
        // octal integer
        case S_OCTAL_INT:
        {
          if (ch == '.')
          {
            state = S_FLOAT;
          }
          else if (ch == 'E' || ch == 'e')
          {
            state = S_FLOAT_E;
          }
          else if (ch == 'L' || ch == 'l')
          {
            state = S_INT_L_SUFFIX;
          }
          else if (ch == 'U' || ch == 'u')
          {
            state = S_INT_U_SUFFIX;
          }
          else if (ch == 'i' && peekChar (s, 1) == '6' && peekChar (s, 2) == '4')
          {
            state = S_INT_I_SUFFIX;
          }
          else if (ch >= '0' && ch <= '7')
          {
            // stay in same state
          }
          else if (ch >= '8' && ch <= '9')
          {
            // we've started as a octal but now have an 8 or a 9, if this token isn't a float then it's
            // an invalid octal int
            octal_error = true;
            state = S_INT;
          }
          else
          {
            kind = LITERAL_INT_TOKEN;
          }
          break;
        }
        // decimal integer
        case S_INT:
        {
          if (ch == '.')
          {
            state = S_FLOAT;
          }
          else if (ch == 'E' || ch == 'e')
          {
            state = S_FLOAT_E;
          }
          else if (ch == 'L' || ch == 'l')
          {
            state = S_INT_L_SUFFIX;
          }
          else if (ch == 'U' || ch == 'u')
          {
            state = S_INT_U_SUFFIX;
          }
          else if (ch == 'i' && peekChar (s, 1) == '6' && peekChar (s, 2) == '4')
          {
            state = S_INT_I_SUFFIX;
          }
          else if (ch >= '0' && ch <= '9')
          {
            // stay in same state
          }
          else
          {
            kind = LITERAL_INT_TOKEN;
          }
          break;
        }
        // integer with l suffix
        case S_INT_L_SUFFIX:
        {
          if (ch == 'U' || ch == 'u')
          {
            // 'lu' suffix so an int, we'll not allow an 'lul' suffix for 'unsinged long long'
            state = S_INT_SUFFIX;
          }
          else if (ch == 'L' || ch == 'l')
          {
            state = S_INT_LL_SUFFIX;
          }
          else
          {
            kind = LITERAL_INT_TOKEN;
          }
          break;
        }
        // integer with u suffix
        case S_INT_U_SUFFIX:
        {
          if (ch == 'L' || ch == 'l')
          {
            // could still be an 'ull' suffix
            state = S_INT_UL_SUFFIX;
          }
          else if (ch == 'i' && peekChar (s, 1) == '6' && peekChar (s, 2) == '4')
          {
            state = S_INT_UI_SUFFIX;
          }
          else
          {
            kind = LITERAL_INT_TOKEN;
          }
          break;
        }
        // integer with ul suffix
        case S_INT_UL_SUFFIX:
        {
          if (ch == 'L' || ch == 'l')
          {
            state = S_INT_SUFFIX;
          }
          else
          {
            kind = LITERAL_INT_TOKEN;
          }
          break;
        }
        // integer with ll suffix
        case S_INT_LL_SUFFIX:
        {
          if (ch == 'U' || ch == 'u')
          {
            state = S_INT_SUFFIX;
          }
          else
          {
            kind = LITERAL_INT_TOKEN;
          }
          break;
        }
        // integer with i suffix, 64 next
        case S_INT_I_SUFFIX:
        {
          state = S_INT_I6_SUFFIX;
          break;
        }
        // integer with i6 suffix, 4 next
        case S_INT_I6_SUFFIX:
        {
          state = S_INT_LL_SUFFIX;
          break;
        }
        // integer with ui suffix, 64 next
        case S_INT_UI_SUFFIX:
        {
          state = S_INT_UI6_SUFFIX;
          break;
        }
        // integer with ui6 suffix, 4 next
        case S_INT_UI6_SUFFIX:
        {
          state = S_INT_SUFFIX;
          break;
        }
        // int with suffix
        case S_INT_SUFFIX:
        {
          kind = LITERAL_INT_TOKEN;
          break;
        }
        // float
        case S_FLOAT:
        {
          if (ch == 'E' || ch == 'e')
          {
            state = S_FLOAT_E;
          }
          else if (ch == 'F' || ch == 'f' || ch == 'L' || ch == 'l')
          {
            state = S_FLOAT_SUFFIX;
          }
          else if (ch >= '0' && ch <= '9')
          {
            // stay in same state
          }
          else
          {
            kind = LITERAL_FLOAT_TOKEN;
          }
          break;
        }
        // float with e
        case S_FLOAT_E:
        {
          if (ch == '+' || ch == '-')
          {
            state = S_FLOAT_E_SIGN;
          }
          else if (ch >= '0' && ch <= '9')
          {
            state = S_FLOAT_EXP;
          }
          else
          {
            // missing exponent, append 0 to make valid
            msg::missingExponentInFloatingLiteral (loc);
            error = true;
            // try to recover
            ident_table.push ('0');
            if (ch == 'F' || ch == 'f' || ch == 'L' || ch == 'l')
            {
              state = S_FLOAT_SUFFIX;
            }
            else
            {
              kind = LITERAL_FLOAT_TOKEN;
            }
          }
          break;
        }
        // float with e and sign
        case S_FLOAT_E_SIGN:
        {
          if (ch >= '0' && ch <= '9')
          {
            state = S_FLOAT_EXP;
          }
          else
          {
            // missing exponent, append 0 to make valid
            msg::missingExponentInFloatingLiteral (loc);
            error = true;
            // try to recover
            ident_table.push ('0');
            if (ch == 'F' || ch == 'f' || ch == 'L' || ch == 'l')
            {
              state = S_FLOAT_SUFFIX;
            }
            else
            {
              kind = LITERAL_FLOAT_TOKEN;
            }
          }
          break;
        }
        // float exponent
        case S_FLOAT_EXP:
        {
          if (ch == 'F' || ch == 'f' || ch == 'L' || ch == 'l')
          {
            state = S_FLOAT_SUFFIX;
          }
          else if (ch >= '0' && ch <= '9')
          {
            // stay in same state
          }
          else
          {
            kind = LITERAL_FLOAT_TOKEN;
          }
          break;
        }
        // float with suffix
        case S_FLOAT_SUFFIX:
        {
          kind = LITERAL_FLOAT_TOKEN;
          break;
        }
        // dot
        case S_DOT:
        {
          assert (ch >= '0' && ch <= '9');
          state = S_FLOAT;
          break;
        }
      }
      if (kind != 0)
      {
        break;
      }
      // char part of lexeme
      ident_table.push (ch);
      ++ s;
    }

    // warn if octal error
    util::Ident lexeme = ident_table.getIdent ();
    if (kind == LITERAL_INT_TOKEN && octal_error)
    {
      msg::octalHasDigitsBeyondRadix (loc, lexeme);
    }

    // set the lexeme if not the same
    if (lexeme != token.getLexeme ())
    {
      // any chars remaining?
      if (* s != 0)
      {
        if (kind == LITERAL_FLOAT_TOKEN)
        {
          msg::invalidFloatingLiteralSuffix (loc, s, lexeme);
        }
        else
        {
          // otherwise literal int or literal zero token
          msg::invalidIntLiteralSuffix (loc, s, lexeme);
        }
      }
      // change the lexeme so expr will be able to correctly get is value  
      token.setLexeme (lexeme);
    }

    // and finally, set it's real kind 
    token.setNumber (kind);
  }
}
#undef LZZ_INLINE
