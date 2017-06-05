// gram_TranslateLiteralChar.cpp
//

#include "gram_TranslateLiteralChar.h"
// library
#include <cstdlib>
#include <cassert>

// gram
#include "gram_Message.h"
#include "gram_ReadHexDigits.h"
#include "gram_ReadOctalDigits.h"

// util
#include "util_Exception.h"
#define LZZ_INLINE inline
namespace gram
{
  unsigned int translateLiteralChar (util::Loc const & loc, char const * str, char const * * next_ch)
  {
    char ch = * str ++;
    assert (ch != 0);
    unsigned int out_ch = ch;
    if (ch == '\\')
    { 
      // escape sequece, read next char and check if valid
      ch = * str ++;
      assert (ch != 0);
      switch (ch)
      {
        // simple escape sequence
        case '\'':
        case '\"':
        case '\?':
        case '\\':
        {
          out_ch = ch;
          break;
        }
        case 'a':
        {
          out_ch = '\a';
          break;
        }
        case 'b':
        {
          out_ch = '\b';
          break;
        }
        case 'f':
        {
          out_ch = '\f';
          break;
        }
        case 'n':
        {
          out_ch = '\n';
          break;
        }
        case 'r':
        {
          out_ch = '\r';
          break;
        }
        case 't':
        {
          out_ch = '\t';
          break;
        }
        case 'v':
        {
          out_ch = '\v';
          break;
        }

        // hex number
        case 'x':
        {
          // read lots of hex numbers
          char out [128];
          if (readHexDigits (str, 128, out, & str) == 0)
          {
            msg::missingHexDigitsInCharLiteral (loc);
            throw util::Exception ();
          }
          out_ch = strtoul (out, 0, 16);
          break;
        }
      
        // octal digit
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        {
          // read no more than two more
          char out [12];
          out [0] = ch;
          readOctalDigits (str, 2, out + 1, & str);
          out_ch = strtoul (out, 0, 8);
          break;
        }

        // universal char
        case 'u':
        case 'U':
        {
          int num_digits = (ch == 'u' ? 4 : 8);
          char out [12];
          if (readHexDigits (str, num_digits, out, & str) != num_digits)
          {
            msg::invalidUniversalChar (loc);
            throw util::Exception ();
          }
          else
          {
            out_ch = strtoul (out, 0, 16);
          }
          break;
        }

        // character not valid, accept it but give a warning
        default:
        {
          out_ch = ch; 
          msg::invalidEscInLiteralChar (loc);
          throw util::Exception ();
        }
      }
    }
    * next_ch = str;
    return out_ch;
  }
}
#undef LZZ_INLINE
