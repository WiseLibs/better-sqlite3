// gram_ObjMacro.h
//

#ifndef LZZ_gram_ObjMacro_h
#define LZZ_gram_ObjMacro_h
// gram
#include "gram_RepMacro.h"
#define LZZ_INLINE inline
namespace gram
{
  class ObjMacro : public RepMacro
  {
  public:
    ObjMacro (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set);
    ~ ObjMacro ();
    MacroKind getKind () const;
  };
}
#undef LZZ_INLINE
#endif
