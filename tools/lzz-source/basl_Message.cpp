// basl_Message.cpp
//

#include "basl_Message.h"
// std lib
#include <algorithm>
#include <iostream>
#include <string>

// util
#include "util_LocToString.h"
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace
{
  using namespace basl;
}
namespace
{
  struct AppendLexeme
  {
    util::String & str;
    void operator () (FreeToken const & free_token) const;
  public:
    explicit AppendLexeme (util::String & str);
    ~ AppendLexeme ();
  };
}
namespace
{
  util::String freeTokenSetToString (FreeTokenVector const & free_token_set);
}
namespace basl
{
  namespace msg
  {
    using namespace ::msg;
  }
}
namespace
{
  LZZ_INLINE void AppendLexeme::operator () (FreeToken const & free_token) const
  {
    util::appendWithSpace (str, free_token.lexeme.c_str ());
  }
}
namespace
{
  LZZ_INLINE AppendLexeme::AppendLexeme (util::String & str)
    : str (str)
              {}
}
namespace
{
  AppendLexeme::~ AppendLexeme ()
              {}
}
namespace
{
  util::String freeTokenSetToString (FreeTokenVector const & free_token_set)
  {
    util::String str;
    for_each (free_token_set.begin (), free_token_set.end (), AppendLexeme (str));
    return str;
  }
}
namespace basl
{
  namespace msg
  {
    void syntaxError (util::Loc const & loc, util::Ident const & lexeme)
  {
    static char const str [] = "Syntax error before '%1'.";
    print (loc, Message (ERROR_MSG, str) << lexeme);
  }
  }
}
namespace basl
{
  namespace msg
  {
    void insertingTokens (util::Loc const & loc, util::Ident const & lexeme, FreeTokenVector const & free_token_set)
  {
    static char const str [] = "Inserting '%2' before '%1'.";
    print (loc, Message (ERROR_MSG, str) << lexeme << freeTokenSetToString (free_token_set));
  }
  }
}
namespace basl
{
  namespace msg
  {
    void replacingTokens (util::Loc const & loc, util::Ident const & lexeme, int num_discard, FreeTokenVector const & free_token_set)
  {
    static char const str1 [] = "Replacing '%1' with '%2'.";
    static char const str2 [] = "Replacing '%1' and next token with '%2'.";
    static char const str3 [] = "Replacing '%1' and next %2 tokens with '%3'.";
    util::String free_token_set_str = freeTokenSetToString (free_token_set);
    if (num_discard == 1)
    {
      print (loc, Message (ERROR_MSG, str1) << lexeme << free_token_set_str);
    }
    else if (num_discard == 2)
    {
      print (loc, Message (ERROR_MSG, str2) << lexeme << free_token_set_str);
    }
    else
    {
      print (loc, Message (ERROR_MSG, str3) << lexeme << (num_discard - 1) << free_token_set_str);
    }
  }
  }
}
namespace basl
{
  namespace msg
  {
    void discardingTokens (util::Loc const & loc, util::Ident const & lexeme, int num_discard)
  {
    static char const str1 [] = "Discarding '%1'.";
    static char const str2 [] = "Discarding '%1' and next token.";
    static char const str3 [] = "Discarding '%1' and next %2 tokens.";
    if (num_discard == 1)
    {
      print (loc, Message (ERROR_MSG, str1) << lexeme);
    }
    else if (num_discard == 2)
    {
      print (loc, Message (ERROR_MSG, str2) << lexeme);
    }
    else
    {
      print (loc, Message (ERROR_MSG, str3) << lexeme << (num_discard - 1));
    }
  }
  }
}
namespace basl
{
  namespace msg
  {
    void movingTokens (util::Loc const & loc, util::Ident const & lexeme1, int num_move, int num, util::Ident const & lexeme2)
  {
    static char const str1 [] = "Moving '%1' after 1 token to the right, before '%2'.";
    static char const str2 [] = "Moving '%1' after %2 tokens to the right, before '%3'.";
    static char const str3 [] = "Moving '%1' and the next token after 1 token to the right, before '%2'.";
    static char const str4 [] = "Moving '%1' and the next token after %2 tokens to the right, before '%3'.";
    static char const str5 [] = "Moving '%1' and the next %2 tokens after 1 token to the right, before '%3'.";
    static char const str6 [] = "Moving '%1' and the next %3 tokens after %2 tokens to the right, before '%4'.";
    if (num == 1)
    {
      if (num_move == 1)
      {
        print (loc, Message (ERROR_MSG, str1) << lexeme1 << lexeme2);
      }
      else
      {
        print (loc, Message (ERROR_MSG, str2) << lexeme1 << num_move << lexeme2);
      }
    }
    else if (num == 2)
    {
      if (num_move == 1)
      {
        print (loc, Message (ERROR_MSG, str3) << lexeme1 << lexeme2);
      }
      else
      {
        print (loc, Message (ERROR_MSG, str4) << lexeme1 << num_move << lexeme2);
      }
    }
    else
    {
      if (num_move == 1)
      {
        print (loc, Message (ERROR_MSG, str5) << lexeme1 << (num - 1) << lexeme2);
      }
      else
      {
        print (loc, Message (ERROR_MSG, str6) << lexeme1 << num_move << (num - 1) << lexeme2);
      }
    }
  }
  }
}
namespace basl
{
  namespace msg
  {
    void syntaxErrorLimitReached (util::Loc const & loc)
  {
    static char const str [] = "Syntax error limit reached.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace basl
{
  namespace msg
  {
    void unableToRecover (util::Loc const & loc)
  {
    static char const str [] = "Unable to recover from syntax error.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
#undef LZZ_INLINE
