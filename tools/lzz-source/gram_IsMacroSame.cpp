// gram_IsMacroSame.cpp
//

#include "gram_IsMacroSame.h"
// std lib
#include <algorithm>

// gram
#include "gram_FuncMacro.h"
#include "gram_GetIdent.h"
#define LZZ_INLINE inline
namespace
{
  struct IsReplTokenSame
  {
    bool first;
    bool operator () (basl::Token const & a, basl::Token const & b);
  public:
    explicit IsReplTokenSame (bool first = true);
    ~ IsReplTokenSame ();
  };
}
namespace
{
  bool IsReplTokenSame::operator () (basl::Token const & a, basl::Token const & b)
  {
    // token same if lexeme same and delimiting space same
    bool result = a.getLexeme () == b.getLexeme ();
    if (first)
    {
      first = false;
    }
    else
    {
      result = result && (a.hasSpaceBefore () == b.hasSpaceBefore ());
    }
    return result;
  }
}
namespace
{
  LZZ_INLINE IsReplTokenSame::IsReplTokenSame (bool first)
    : first (first)
       {}
}
namespace
{
  IsReplTokenSame::~ IsReplTokenSame ()
       {}
}
namespace gram
{
  bool isMacroSame (MacroPtr const & macro, bool is_func, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set)
  {
    bool result = false;
    int kind = is_func ? FUNC_MACRO : OBJ_MACRO;
    if (kind == macro->getKind ())
    {
      bool same_params = true; 
      if (kind == FUNC_MACRO)
      {
        FuncMacro const & func_macro = static_cast <FuncMacro const &> (* macro);
        same_params = (func_macro.getNumParams () == param_set.size () && func_macro.hasVarArgs () == var && 
            std::equal (param_set.begin (), param_set.end (), func_macro.getParamSet ().begin ()));
      }
      basl::TokenVector const & macro_rep_set = static_cast <RepMacro const &> (* macro).getRepSet ();
      result = (same_params && rep_set.size () == macro_rep_set.size () &&
          std::equal (rep_set.begin (), rep_set.end (), macro_rep_set.begin (), IsReplTokenSame ()));
    }
    return result;
  }
}
#undef LZZ_INLINE
