// gram_Macro.h
//

#ifndef LZZ_gram_Macro_h
#define LZZ_gram_Macro_h
// gram
#include "gram_MacroKind.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  class Macro
  {
    util::Loc m_loc;
    util::Ident m_name;
  public:
    Macro (util::Loc const & loc, util::Ident const & name);
    virtual ~ Macro () = 0;
    util::Loc const & getLoc () const;
    util::Ident const & getName () const;
    virtual MacroKind getKind () const = 0;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_Macro.inl"
#endif
#endif
