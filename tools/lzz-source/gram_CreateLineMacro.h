// gram_CreateLineMacro.h
//

#ifndef LZZ_gram_CreateLineMacro_h
#define LZZ_gram_CreateLineMacro_h
// gram
#include "gram_MacroPtr.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createLineMacro (util::Loc const & loc, util::Ident const & name);
}
#undef LZZ_INLINE
#endif
