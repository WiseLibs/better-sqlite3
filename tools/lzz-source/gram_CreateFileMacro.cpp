// gram_CreateFileMacro.cpp
//

#include "gram_CreateFileMacro.h"
// gram
#include "gram_FileMacro.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createFileMacro (util::Loc const & loc, util::Ident const & name)
  {
    return new FileMacro (loc, name);
  }
}
#undef LZZ_INLINE
