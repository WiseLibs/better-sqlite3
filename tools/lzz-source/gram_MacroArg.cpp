// gram_MacroArg.cpp
//

#include "gram_MacroArg.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_MacroArg.inl"
#endif
// gram
#define LZZ_INLINE inline
namespace gram
{
  MacroArg::MacroArg (basl::TokenVector const & token_set)
    : m_token_set (token_set)
    {}
}
namespace gram
{
  MacroArg::~ MacroArg ()
    {}
}
#undef LZZ_INLINE
