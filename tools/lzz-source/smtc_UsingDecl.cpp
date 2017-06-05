// smtc_UsingDecl.cpp
//

#include "smtc_UsingDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_UsingDecl.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  UsingDecl::UsingDecl (NamePtr const & name)
    : m_name (name)
    {}
}
namespace smtc
{
  UsingDecl::~ UsingDecl ()
    {}
}
#undef LZZ_INLINE
