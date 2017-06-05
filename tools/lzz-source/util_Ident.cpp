// util_Ident.cpp
//

#include "util_Ident.h"
#ifndef LZZ_ENABLE_INLINE
#include "util_Ident.inl"
#endif
#define LZZ_INLINE inline
namespace util
{
  Ident::operator char const * () const
    {
      return m_key;
    }
}
#undef LZZ_INLINE
