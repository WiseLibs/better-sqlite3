// gram_BuildMacro.cpp
//

#include "gram_BuildMacro.h"
// gram
#include "gram_CreateFuncMacro.h"
#include "gram_CreateObjMacro.h"
#include "gram_GetIdent.h"
#include "gram_TokenNumber.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr buildMacro (util::Loc const & loc, util::Ident const & name, bool is_func, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set)
  {
    MacroPtr macro;
    if (is_func)
    {
      macro = createFuncMacro (loc, name, param_set, var, rep_set);
    }
    else
    {
      macro = createObjMacro (loc, name, rep_set);
    }
    return macro;
  }
}
#undef LZZ_INLINE
