// gram_CreateFuncMacro.h
//

#ifndef LZZ_gram_CreateFuncMacro_h
#define LZZ_gram_CreateFuncMacro_h
// gram
#include "gram_MacroPtr.h"

// basil
#include "basl_TokenVector.h"

// util
#include "util_IdentVector.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createFuncMacro (util::Loc const & loc, util::Ident const & name, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set);
}
#undef LZZ_INLINE
#endif
