// gram_CheckMacroRepSet.cpp
//

#include "gram_CheckMacroRepSet.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_CheckMacroRepSet.inl"
#endif
// std lib
#include <algorithm>

// gram
#include "gram_GetIdent.h"
#include "gram_Message.h"
#include "gram_TokenNumber.h"
#define LZZ_INLINE inline
namespace gram
{
  bool checkObjMacroRepSet (basl::TokenVector & rep_set)
  {
    bool t = ! rep_set.empty ();
    for (basl::TokenVectorConstIter nxt = rep_set.begin (), end = rep_set.end (); nxt != end; ++ nxt)
    {
      basl::Token const & token = * nxt;
      if (token.getNumber () == DBLHASH_TOKEN)
      {
        if (t)
        {
          msg::dblHashFirstOrLastToken (token.getLoc ());
          return false;
        }
        t = true;
      }
      else
      {
        t = false;
      }
    }
    if (t)
    {
      msg::dblHashFirstOrLastToken (rep_set.back ().getLoc ());
      return false;
    }
    return true;
  }
}
namespace gram
{
  bool checkFuncMacroRepSet (util::IdentVector const & param_set, bool var, basl::TokenVector & rep_set)
  {
    bool t = ! rep_set.empty (), p = false;
    for (basl::TokenVectorIter nxt = rep_set.begin (), end = rep_set.end (); nxt != end; ++ nxt)
    {
      basl::Token & token = * nxt;
      int number = token.getNumber ();
      util::Loc const & loc = token.getLoc ();
      if (number == DBLHASH_TOKEN)
      {
        if (p)
        {
          msg::hashNotPrecedingParam (loc);
          return false;
        }
        else if (t)
        {
          msg::dblHashFirstOrLastToken (loc);
          return false;
        }
        t = true;
        p = false;
      }
      else if (number == HASH_TOKEN)
      {
        if (p)
        {
          msg::hashNotPrecedingParam (loc);
          return false;
        }
        p = true;
      }
      else if (number == IDENT_TOKEN)
      {
        util::Ident const & lexeme = token.getLexeme ();
        util::IdentVectorConstIter i = std::find (param_set.begin (), param_set.end (), lexeme);
        if (i != param_set.end ())
        {
          token.setNumber (IDENT_PARAM_START_TOKEN + (i - param_set.begin ()));
        }
        else if (p)
        {
          msg::hashNotPrecedingParam (loc);
          return false;
        }
        else if (lexeme == va_args_ident)
        {
          // warn only, replacment list is still valid
          if (var)
          {
            msg::vaArgsUsedWithNamedVarArg (loc);
          }
          else
          {
            msg::vaArgsUsedInNonVarMacro (loc);
          }
        }
        t = false;
        p = false;
      }
      else
      {
        if (p)
        {
          msg::hashNotPrecedingParam (loc);
          return false;
        }
        t = false;
        p = false;
      }
    }
    if (p)
    {
      msg::hashNotPrecedingParam (rep_set.back ().getLoc ());
      return false;
    }
    else if (t)
    {
      msg::dblHashFirstOrLastToken (rep_set.back ().getLoc ());
      return false;
    }
    return true;
  }
}
#undef LZZ_INLINE
