// smtc_UsingDir.cpp
//

#include "smtc_UsingDir.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_UsingDir.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  UsingDir::UsingDir (NamePtr const & name)
    : m_name (name)
    {}
}
namespace smtc
{
  UsingDir::~ UsingDir ()
    {}
}
#undef LZZ_INLINE
