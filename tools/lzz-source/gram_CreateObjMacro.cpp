// gram_CreateObjMacro.cpp
//

#include "gram_CreateObjMacro.h"
// gram
#include "gram_ObjMacro.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createObjMacro (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set)
  {
    return new ObjMacro (loc, name, rep_set);
  }
}
#undef LZZ_INLINE
