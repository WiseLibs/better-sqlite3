// smtc_Enum.cpp
//

#include "smtc_Enum.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Enum.inl"
#endif
// semantic
#define LZZ_INLINE inline
namespace smtc
{
  Enum::Enum (util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set)
    : m_loc (loc), m_name (name), m_enumtor_set (enumtor_set)
    {}
}
namespace smtc
{
  Enum::~ Enum ()
    {}
}
#undef LZZ_INLINE
