// gram_CreateFileMacro.h
//

#ifndef LZZ_gram_CreateFileMacro_h
#define LZZ_gram_CreateFileMacro_h
// gram
#include "gram_MacroPtr.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createFileMacro (util::Loc const & loc, util::Ident const & name);
}
#undef LZZ_INLINE
#endif
