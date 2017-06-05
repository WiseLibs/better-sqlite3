// gram_LexDefineLine.cpp
//

#include "gram_LexDefineLine.h"
// std lib
#include <algorithm>

// gram
#include "gram_DiscardRestOfLine.h"
#include "gram_GetIdent.h"
#include "gram_LexRestOfLine.h"
#include "gram_Lexer.h"
#include "gram_Message.h"
#include "gram_TokenNumber.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  bool lexFuncMacroParamList (Lexer & lexer, util::IdentVector & param_set, bool & var);
}
namespace
{
  bool lexFuncMacroParamList (Lexer & lexer, util::IdentVector & param_set, bool & var)
  {
    // read first token
    util::Loc loc;
    basl::Token token;
    // read parameter, must not be end of line
    if (! lexer.getNextToken (loc, token))
    {
      msg::macroParamListSyntaxErrorAtEol (loc);
      return false;
    }
    if (token.getNumber () != RPAREN_TOKEN)
    {
      for (;;)
      {
        // must be a parameter or an ellipse
        if (token.getNumber () == ELLIPSE_TOKEN)
        {
          // '__VA_ARGS__' is implicitly the last parameter; can take a variable number of args
          param_set.push_back (va_args_ident);
          var = true;
          break;
        }
        if (token.getNumber () != IDENT_TOKEN)
        {
          msg::macroParamListSyntaxErrorBeforeToken (loc, token.getLexeme ());
          discardRestOfLine (lexer);
          return false;
        }
        util::Ident const & lexeme = token.getLexeme ();
        // cannot be __VA_ARGS__
        if (lexeme == va_args_ident)
        {
          msg::explicitVaArgsMacroParam (loc);
          discardRestOfLine (lexer);
          return false;
        }
        // check for duplicate param
        if (std::find (param_set.begin (), param_set.end (), lexeme) != param_set.end ())
        {
          msg::duplicateMacroParam (loc, lexeme);
          discardRestOfLine (lexer);
          return false;
        }
        param_set.push_back (lexeme);
        if (! lexer.getNextToken (loc, token))
        {
          msg::macroParamListSyntaxErrorAtEol (loc);
          return false;
        }
        // next token should be comma or ellipse
        if (token.getNumber () == ELLIPSE_TOKEN)
        {
          // last param can take variable number of args
          var = true;
          break;
        }
        else if (token.getNumber () != COMMA_TOKEN)
        {
          break;
        }
        if (! lexer.getNextToken (loc, token))
        {
          msg::macroParamListSyntaxErrorAtEol (loc);
          return false;
        }
      }
      // if var then last token was an ellipse so get next token
      if (var && ! lexer.getNextToken (loc, token))
      {
        msg::macroParamListSyntaxErrorAtEol (loc);
        return false;
      }
      if (token.getNumber () != RPAREN_TOKEN)
      {
        msg::macroParamListSyntaxErrorBeforeToken (loc, token.getLexeme ());
        discardRestOfLine (lexer);
        return false;
      }
    }
    return true;
  }
}
namespace gram
{
  bool lexDefineLine (Lexer & lexer, bool is_cmd, util::Loc const & dir_loc, util::Loc & name_loc, util::Ident & name, bool & is_func, util::IdentVector & param_set, bool & var, basl::TokenVector & rep_set)
  {
    util::Loc loc;
    basl::Token token;
    // get macro name
    char const * dir_name = "define";
    if (! lexer.getNextToken (loc, token))
    {
      msg::missingMacroIdent (dir_loc, dir_name);
      return false;
    }
    // should be an identifier
    if (token.getNumber () != IDENT_TOKEN)
    {
      msg::missingMacroIdent (loc, dir_name);
      discardRestOfLine (lexer);
      return false;
    }
    name_loc = loc;
    name = token.getLexeme ();
    // get replacment set, func macro if left paren is next with no white space
    is_func = false;
    bool has_asgn = false;
    if (lexer.getNextToken (token))
    {
      if (token.getNumber () == LPAREN_TOKEN && ! token.hasSpaceBefore ())
      {
        // lex param list, if any errors will discard remaining tokens on line
        if (! lexFuncMacroParamList (lexer, param_set, var))
        {
          return false;
        }
        is_func = true;
        if (lexer.getNextToken (token))
        {
          if (is_cmd && token.getNumber () == ASSIGN_TOKEN)
          {
            has_asgn = true;
          }
          else
          {
            rep_set.push_back (token);
          }
          lexRestOfLine (lexer, rep_set);
        }
      }
      else
      {
        if (is_cmd && token.getNumber () == ASSIGN_TOKEN)
        {
          has_asgn = true;
        }
        else
        {
          rep_set.push_back (token);
        }
        lexRestOfLine (lexer, rep_set);
      }
    }
    // if on command line and replacement set is empty without assignment then replacment set is '1'
    if (is_cmd && ! has_asgn && rep_set.empty ())
    {
      rep_set.push_back (basl::Token (LITERAL_INT_TOKEN, util::Loc (), getIdent ("1")));
    }
    return true;
  }
}
#undef LZZ_INLINE
