// gram_MacroFilter.cpp
//

#include "gram_MacroFilter.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_MacroFilter.inl"
#endif
// std lib
#include <algorithm>

// gram

#include "gram_CreateMacroArg.h"
#include "gram_FuncMacro.h"
#include "gram_GetIdent.h"
#include "gram_LexRestOfLine.h"
#include "gram_Lexer.h"
#include "gram_MacroArg.h"
#include "gram_MacroTable.h"
#include "gram_Message.h"
#include "gram_ObjMacro.h"
#include "gram_TokenNumber.h"

// util
#include "util_Exception.h"
#include "util_IntToString.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  basl::Token stringizeTokenSet (util::Loc const & loc, basl::TokenVector const & token_set);
}
namespace
{
  void concatToken (util::Loc const & sub_loc, util::Loc const & op_loc, basl::Token const & token, basl::TokenVector & token_set);
}
namespace
{
  class ArgMacroFilter : public MacroFilter
  {
  public:
    explicit ArgMacroFilter (util::IdentVector & history, basl::TokenDeque & out_set);
    ~ ArgMacroFilter ();
  };
}
namespace
{
  basl::Token stringizeTokenSet (util::Loc const & loc, basl::TokenVector const & token_set)
  {
    util::String str ("\"");
    bool first = true;
    for (basl::TokenVectorConstIter beg = token_set.begin (), end = token_set.end (); beg != end; ++ beg)
    {
      basl::Token const & token = * beg;
      // 16.3.2p2: white space before the first token and after the last token is deleted
      if (first)
      {
        first = false;
      }
      else if (token.hasSpaceBefore ())
      {
        str += ' ';
      }
      if (token.getNumber () == LITERAL_STRING_TOKEN || token.getNumber () == LITERAL_CHAR_TOKEN)
      {
        // prefix " and \ characters with backslash
        for (char const * s = token.getLexeme ().c_str (); * s != 0; ++ s)
        {
          // but don't escape the backslash preceding a unicode character
          if (* s == '\"' || * s == '\\' && (* (s + 1) == 0 || ! (* (s + 1) == 'u' || * (s + 1) == 'U')))
          {
            str += '\\';
          }
          str += * s;
        }
      }
      else
      {
        str += token.getLexeme ().c_str ();
      }
    }
    str += '\"';
    return basl::Token (LITERAL_STRING_TOKEN, loc, getIdent (str));
  }
}
namespace
{
  void concatToken (util::Loc const & sub_loc, util::Loc const & op_loc, basl::Token const & token, basl::TokenVector & token_set)
  {
    if (token_set.empty ())
    {
      token_set.push_back (token);
    }
    else
    {
      basl::Token back_token = token_set.back ();
      token_set.pop_back ();
      util::String str = back_token.getLexeme ().c_str ();
      str += token.getLexeme ().c_str ();
      Lexer lexer (str, back_token.getLoc ());
      if (lexRestOfLine (lexer, token_set) != 1)
      {
        msg::cannotConcatTokens (sub_loc, back_token.getLexeme (), token.getLexeme (), op_loc);
      }
    }
  }
}
namespace
{
  LZZ_INLINE ArgMacroFilter::ArgMacroFilter (util::IdentVector & history, basl::TokenDeque & out_set)
    : MacroFilter (false, false, history, out_set)
        {}
}
namespace
{
  ArgMacroFilter::~ ArgMacroFilter ()
        {}
}
namespace gram
{
  void MacroFilter::next (basl::TokenVector const & in_set)
    {
      for (basl::TokenVectorConstIter beg = in_set.begin (), end = in_set.end (); beg != end; ++ beg)
      {
        next (* beg);
      }
    }
}
namespace gram
{
  void MacroFilter::next (basl::Token const & in_token)
    {
      basl::Token token (in_token);
      util::Loc const & loc = token.getLoc ();
      int number = token.getNumber ();
      // assume token is passed through filter
      bool pass_token = true;
      switch (state)
      {
        // maybe func macro
        case MAYBE_FUNC_STATE:
        {
          // func macro if left paren
          if (number == LPAREN_TOKEN)
          {
            // collect function args, do not output token
            pass_token = false;
            state = FUNC_ARG_STATE;
            break;
          }
          // otherwise name was not a macro, output func macro token and go to start state
          out_set.push_back (func_macro_token);
          // fall through to start state with same token
          state = START_STATE;
        }

        // start
        case START_STATE:
        {
          // if identifier check if macro name
          if (number == IDENT_TOKEN)
          {
            util::Ident const & name = token.getLexeme ();
            if (is_if && name == defined_ident)
            {
              // warn if found during substitution
              if (is_sub)
              {
                msg::definedInIfMacro (sub_loc, token.getLoc ());
              }
              state = IF_DEFINED_STATE;
            }
            else if (! token.isRecSubMacro ())
            {
              MacroPtr macro;
              if (isMacro (name, macro))
              {
                // check if macro already replaced
                if (isMacroInHistory (name))
                {
                  token.setRecSubMacro ();
                }
                else
                {
                  // do not pass token
                  pass_token = false;
                  // found a macro token not output
                  MacroKind macro_kind = macro->getKind ();
                  if (macro_kind == OBJ_MACRO)
                  {
                    // substitute object macro replacement set
                    basl::TokenVector const & rep_set = static_cast <RepMacro const &> (* macro).getRepSet ();
                    subObjRepSet (loc, name, rep_set);
                  }
                  else if (macro_kind == FILE_MACRO)
                  {
                    // __FILE__ macro
                    util::Loc const & file_loc = is_sub ? sub_loc : loc;
                    util::String lexeme_str;
                    lexeme_str += '\"';
                    // use name as given (g++ does the same)
                    lexeme_str += file_loc.getFilename ().getName ();
                    lexeme_str += '\"';
                    basl::TokenVector rep_set;
                    rep_set.push_back (basl::Token (LITERAL_STRING_TOKEN, loc, getIdent (lexeme_str)));
                    subObjRepSet (loc, name, rep_set);
                  }
                  else if (macro_kind == LINE_MACRO)
                  {
                    // __LINE__ macro
                    util::Loc const & line_loc = is_sub ? sub_loc : loc;
                    util::String lexeme_str = util::intToString (line_loc.getLine ());
                    basl::TokenVector rep_set;
                    rep_set.push_back (basl::Token (LITERAL_INT_TOKEN, loc, getIdent (lexeme_str)));
                    subObjRepSet (loc, name, rep_set);
                  }
                  else
                  {
                    // save token and macro
                    func_macro_token = getPassToken (token);
                    func_macro = macro;
                    // get number of params and check if var
                    num_param = static_cast <FuncMacro const &> (* macro).getNumParams ();
                    var = static_cast <FuncMacro const &> (* macro).hasVarArgs ();
                    // maybe function, wait until left parenthesis
                    state = MAYBE_FUNC_STATE;
                  }
                }
              }
            }
          }
          break;
        }

        // defined
        case IF_DEFINED_STATE:
        {
          if (number == LPAREN_TOKEN)
          {
            state = IF_DEFINED_LPAREN_STATE;
          }
          else
          {
            state = START_STATE;
          }
          break;
        }

        // defined followed by left paren
        case IF_DEFINED_LPAREN_STATE:
        {
          state = START_STATE;
          break;
        }

        // func args
        case FUNC_ARG_STATE:
        {
          // do not pass token
          pass_token = false;
          
          // end of argument if non-nested comma or right paren
          if (nest == 0 && (number == RPAREN_TOKEN || number == COMMA_TOKEN && ! (var && arg_set.size () + 1 >= num_param)))
          {
            if (! arg_token_set.empty ())
            {
              // add next arg and clear arg set
              arg_set.push_back (createMacroArg (arg_token_set));
              arg_token_set.clear ();
            }
            else if (number == COMMA_TOKEN || ! arg_set.empty () || num_param == 1 && ! var)
            {
              // undefined behavior (16.3/10)
              msg::funcMacroArgEmpty (token.getLoc ());
              // add next arg
              arg_set.push_back (createMacroArg (arg_token_set));
            }
            // end of arg list if right paren
            if (number == RPAREN_TOKEN)
            {
              MacroPtr macro = func_macro;
              basl::Token macro_token = func_macro_token;
              util::Loc const & macro_token_loc = macro_token.getLoc ();
              // check number of args
              int num_arg = arg_set.size ();
              if (var && num_arg + 1 == num_param)
              {
                // add empty arg for var param
                arg_set.push_back (createMacroArg (arg_token_set));
                ++ num_arg;
              }
              if (num_arg != num_param)
              {
                util::Ident const & macro_name = func_macro->getName ();
                if (var)
                {
                  msg::badVarMacroNumArg (macro_token_loc, macro_name, num_arg, num_param - 1);
                }
                else
                {
                  msg::badMacroNumArg (macro_token_loc, macro_name, num_arg, num_param);
                }
                throw util::Exception ();
              }
              basl::TokenVector const & rep_set = static_cast <FuncMacro const &> (* func_macro).getRepSet ();
              if (! rep_set.empty ())
              {
                MacroArgPtrVector func_arg_set (arg_set);
                arg_set.clear ();
                state = START_STATE;
                subFuncRepSet (macro_token.getLoc (), macro->getName (), rep_set, func_arg_set, var);
              }
              else
              {
                arg_set.clear ();
                state = START_STATE;
              }
            }
          }
          else 
          {
            // adjust nesting level
            if (number == LPAREN_TOKEN)
            {
              ++ nest;
            }
            else if (number == RPAREN_TOKEN)
            {
              -- nest;
            }
            // add arg token
            arg_token_set.push_back (token);
          }
          break;
        }
      }
      
      // pass token?
      if (pass_token)
      {
        passToken (token);
      }
    }
}
namespace gram
{
  void MacroFilter::flush ()
    {
      if (state == FUNC_ARG_STATE)
      {
        // eof in arg list, fatal error
        msg::eofInMacroArgList (func_macro_token.getLoc ());
        throw util::Exception ();
      }
      if (state == MAYBE_FUNC_STATE)
      {
        // macro token already passed to just append to out_set
        out_set.push_back (func_macro_token);
      }
      // back to start state
      state = START_STATE;
    }
}
namespace gram
{
  bool MacroFilter::isMacroInHistory (util::Ident const & name)
    {
      return std::find (history.begin (), history.end (), name) != history.end ();
    }
}
namespace gram
{
  basl::Token MacroFilter::getPassToken (basl::Token const & token)
    {
      basl::Token res_token (token);
      if (is_sub)
      {
        res_token.setLoc (sub_loc);
        // we need this flag for prettyprinting tokens
        res_token.setFromMacro ();
      }
      return res_token;
    }
}
namespace gram
{
  void MacroFilter::passToken (basl::Token const & token)
    {
      out_set.push_back (getPassToken (token));
    }
}
namespace gram
{
  void MacroFilter::subObjRepSet (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set)
    {
      if (is_sub)
      {
        subObjRepSet (name, rep_set);
      }
      else
      {
        is_sub = true;
        sub_loc = loc;
        subObjRepSet (name, rep_set);
        is_sub = false;
      }
    }
}
namespace gram
{
  void MacroFilter::subObjRepSet (util::Ident const & name, basl::TokenVector const & rep_set)
    {
      basl::TokenVector token_set;
      for (basl::TokenVectorConstIter nxt = rep_set.begin (), end = rep_set.end (); nxt != end; ++ nxt)
      {
        basl::Token const & token = * nxt;
        token_set.push_back (token);
        while (nxt + 1 != end && (* (nxt + 1)).getNumber () == DBLHASH_TOKEN)
        {
          ++ nxt;
          util::Loc const & op_loc = (* nxt).getLoc ();
          ++ nxt;
          concatToken (sub_loc, op_loc, * nxt, token_set);
        }
        next (name, token_set);
        token_set.clear ();
      }
    }
}
namespace gram
{
  void MacroFilter::subFuncRepSet (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set, MacroArgPtrVector const & arg_set, bool var)
    {
      if (is_sub)
      {
        subFuncRepSet (name, rep_set, arg_set, var);
      }
      else
      {
        is_sub = true;
        sub_loc = loc;
        subFuncRepSet (name, rep_set, arg_set, var);
        is_sub = false;
      }
    }
}
namespace gram
{
  void MacroFilter::subFuncRepSet (util::Ident const & name, basl::TokenVector const & rep_set, MacroArgPtrVector const & arg_set, bool var)
    {
      basl::TokenVector token_set;
      for (basl::TokenVectorConstIter nxt = rep_set.begin (), end = rep_set.end (); nxt != end; ++ nxt)
      {
        basl::Token const & token = * nxt;
        int number = token.getNumber ();
        if (number == HASH_TOKEN)
        {
          ++ nxt;
          basl::Token const & token = * nxt;
          int param = token.getNumber () - IDENT_PARAM_START_TOKEN;
          basl::TokenVector const & arg_token_set = arg_set [param]->getTokenSet ();
          token_set.push_back (stringizeTokenSet (token.getLoc (), arg_token_set));
        }
        else if (number >= IDENT_PARAM_START_TOKEN)
        {
          int param = number - IDENT_PARAM_START_TOKEN;
          basl::TokenVector const & arg_token_set = arg_set [param]->getTokenSet ();
          if (nxt + 1 != end && (* (nxt + 1)).getNumber () == DBLHASH_TOKEN)
          {
            token_set.insert (token_set.end (), arg_token_set.begin (), arg_token_set.end ());
          }
          else
          {
            // pass arg tokens through new filter with same history
            basl::TokenDeque arg_out_set;
            ArgMacroFilter arg_filter (history, arg_out_set);
            arg_filter.next (arg_token_set);
            arg_filter.flush ();
            token_set.insert (token_set.end (), arg_out_set.begin (), arg_out_set.end ());
          }
        }
        else
        {
          token_set.push_back (token);
        }
        while (nxt + 1 != end && (* (nxt + 1)).getNumber () == DBLHASH_TOKEN)
        {
          ++ nxt;
          util::Loc const & op_loc = (* nxt).getLoc ();
          ++ nxt;
          basl::Token const & token = * nxt;
          int number = token.getNumber ();
          if (number == HASH_TOKEN)
          {
            ++ nxt;
            basl::Token const & token = * nxt;
            int param = token.getNumber () - IDENT_PARAM_START_TOKEN;
            basl::TokenVector const & arg_token_set = arg_set [param]->getTokenSet ();
            concatToken (sub_loc, op_loc, stringizeTokenSet (token.getLoc (), arg_token_set), token_set);
          }
          else if (number >= IDENT_PARAM_START_TOKEN)
          {
            int param = number - IDENT_PARAM_START_TOKEN;
            basl::TokenVector const & arg_token_set = arg_set [param]->getTokenSet ();
            // remove last comma if param is var param and arg set is empty 
            if (var && param == arg_set.size () - 1 && ! token_set.empty () && token_set.back ().getNumber () == COMMA_TOKEN)
            {
              if (arg_token_set.empty ())
              {
                token_set.pop_back ();
              }
              else
              {
                token_set.insert (token_set.end (), arg_token_set.begin (), arg_token_set.end ());
              }
            }            
            else if (! arg_token_set.empty ())
            {
              concatToken (sub_loc, op_loc, arg_token_set.front (), token_set);
              token_set.insert (token_set.end (), arg_token_set.begin () + 1, arg_token_set.end ());
            }
          }
          else
          {
            concatToken (sub_loc, op_loc, token, token_set);
          }
        }
        next (name, token_set);
        token_set.clear ();
      }
    }
}
namespace gram
{
  void MacroFilter::next (util::Ident const & name, basl::TokenVector const & in_set)
    {
      history.push_back (name);
      next (in_set);
      history.pop_back ();
    }
}
namespace gram
{
  MacroFilter::~ MacroFilter ()
        {}
}
namespace gram
{
  FileMacroFilter::~ FileMacroFilter ()
        {}
}
namespace gram
{
  HashIfMacroFilter::~ HashIfMacroFilter ()
        {}
}
#undef LZZ_INLINE
