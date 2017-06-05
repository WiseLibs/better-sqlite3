// smtc_MbrInit.cpp
//

#include "smtc_MbrInit.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_MbrInit.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  MbrInit::MbrInit (NamePtr const & name, util::String const & arg_set)
    : m_name (name), m_arg_set (arg_set)
    {}
}
namespace smtc
{
  MbrInit::~ MbrInit ()
    {}
}
#undef LZZ_INLINE
