// gram_CheckMacroRepSet.h
//

#ifndef LZZ_gram_CheckMacroRepSet_h
#define LZZ_gram_CheckMacroRepSet_h
// gram
#include "basl_TokenVector.h"

// util
#include "util_IdentVector.h"
#define LZZ_INLINE inline
namespace gram
{
  bool checkObjMacroRepSet (basl::TokenVector & rep_set);
}
namespace gram
{
  bool checkFuncMacroRepSet (util::IdentVector const & param_set, bool var, basl::TokenVector & rep_set);
}
namespace gram
{
  bool checkMacroRepSet (bool is_func, util::IdentVector const & param_set, bool var, basl::TokenVector & rep_set);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_CheckMacroRepSet.inl"
#endif
#endif
