// gram_CreateFuncMacro.cpp
//

#include "gram_CreateFuncMacro.h"
// gram
#include "gram_FuncMacro.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createFuncMacro (util::Loc const & loc, util::Ident const & name, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set)
  {
    return new FuncMacro (loc, name, param_set, var, rep_set);
  }
}
#undef LZZ_INLINE
