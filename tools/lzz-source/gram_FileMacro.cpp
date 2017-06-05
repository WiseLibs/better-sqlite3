// gram_FileMacro.cpp
//

#include "gram_FileMacro.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_FileMacro.inl"
#endif
#define LZZ_INLINE inline
namespace gram
{
  FileMacro::~ FileMacro ()
    {}
}
namespace gram
{
  MacroKind FileMacro::getKind () const
    {
      return FILE_MACRO;
    }
}
#undef LZZ_INLINE
