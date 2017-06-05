// gram_FileMacro.h
//

#ifndef LZZ_gram_FileMacro_h
#define LZZ_gram_FileMacro_h
// gram
#include "gram_Macro.h"
#define LZZ_INLINE inline
namespace gram
{
  class FileMacro : public Macro
  {
  public:
    FileMacro (util::Loc const & loc, util::Ident const & name);
    ~ FileMacro ();
    MacroKind getKind () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_FileMacro.inl"
#endif
#endif
