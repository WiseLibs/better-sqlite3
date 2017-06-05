// gram_CreateLineMacro.cpp
//

#include "gram_CreateLineMacro.h"
// gram
#include "gram_LineMacro.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createLineMacro (util::Loc const & loc, util::Ident const & name)
  {
    return new LineMacro (loc, name);
  }
}
#undef LZZ_INLINE
