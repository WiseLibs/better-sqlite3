// gram_CreateObjMacro.h
//

#ifndef LZZ_gram_CreateObjMacro_h
#define LZZ_gram_CreateObjMacro_h
// gram
#include "gram_MacroPtr.h"

// basil
#include "basl_TokenVector.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  MacroPtr createObjMacro (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set);
}
#undef LZZ_INLINE
#endif
