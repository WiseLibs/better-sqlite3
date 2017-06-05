// gram_LineMacro.cpp
//

#include "gram_LineMacro.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_LineMacro.inl"
#endif
#define LZZ_INLINE inline
namespace gram
{
  LineMacro::~ LineMacro ()
    {}
}
namespace gram
{
  MacroKind LineMacro::getKind () const
    {
      return LINE_MACRO;
    }
}
#undef LZZ_INLINE
