// smtc_Param.cpp
//

#include "smtc_Param.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Param.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  Param::Param (NamePtr const & name)
    : m_name (name)
    {}
}
namespace smtc
{
  Param::~ Param ()
    {}
}
#undef LZZ_INLINE
