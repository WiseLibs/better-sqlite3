// gram_Macro.cpp
//

#include "gram_Macro.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_Macro.inl"
#endif
// gram
#define LZZ_INLINE inline
namespace gram
{
  Macro::Macro (util::Loc const & loc, util::Ident const & name)
    : m_loc (loc), m_name (name)
    {}
}
#undef LZZ_INLINE
