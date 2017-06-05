// gram_CreateMacroArg.cpp
//

#include "gram_CreateMacroArg.h"
// gram
#include "gram_MacroArg.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroArgPtr createMacroArg (basl::TokenVector const & token_set)
  {
    return new MacroArg (token_set);
  }
}
#undef LZZ_INLINE
