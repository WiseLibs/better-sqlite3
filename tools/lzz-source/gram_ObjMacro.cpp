// gram_ObjMacro.cpp
//

#include "gram_ObjMacro.h"
// gram
#define LZZ_INLINE inline
namespace gram
{
  ObjMacro::ObjMacro (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set)
    : RepMacro (loc, name, rep_set)
    {}
}
namespace gram
{
  ObjMacro::~ ObjMacro ()
    {}
}
namespace gram
{
  MacroKind ObjMacro::getKind () const
    {
      return OBJ_MACRO;
    }
}
#undef LZZ_INLINE
