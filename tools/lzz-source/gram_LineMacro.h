// gram_LineMacro.h
//

#ifndef LZZ_gram_LineMacro_h
#define LZZ_gram_LineMacro_h
// gram
#include "gram_Macro.h"
#define LZZ_INLINE inline
namespace gram
{
  class LineMacro : public Macro
  {
  public:
    LineMacro (util::Loc const & loc, util::Ident const & name);
    ~ LineMacro ();
    MacroKind getKind () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_LineMacro.inl"
#endif
#endif
