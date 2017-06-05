// gram_BuildMacro.h
//

#ifndef LZZ_gram_BuildMacro_h
#define LZZ_gram_BuildMacro_h
// gram
#include "gram_MacroKind.h"
#include "gram_MacroPtr.h"

// basil
#include "basl_TokenVector.h"

// util
#include "util_IdentVector.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr buildMacro (util::Loc const & loc, util::Ident const & name, bool is_func, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set);
}
#undef LZZ_INLINE
#endif
