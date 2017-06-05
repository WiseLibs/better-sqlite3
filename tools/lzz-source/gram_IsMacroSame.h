// gram_IsMacroSame.h
//

#ifndef LZZ_gram_IsMacroSame_h
#define LZZ_gram_IsMacroSame_h
// gram
#include "gram_MacroPtr.h"

// basil
#include "basl_TokenVector.h"

// util
#include "util_IdentVector.h"
#define LZZ_INLINE inline
namespace gram
{
  bool isMacroSame (MacroPtr const & macro, bool is_func, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set);
}
#undef LZZ_INLINE
#endif
