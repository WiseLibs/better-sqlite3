// gram_CreateMacroArg.h
//

#ifndef LZZ_gram_CreateMacroArg_h
#define LZZ_gram_CreateMacroArg_h
// gram
#include "gram_MacroArgPtr.h"

// basil
#include "basl_TokenVector.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroArgPtr createMacroArg (basl::TokenVector const & token_set);
}
#undef LZZ_INLINE
#endif
