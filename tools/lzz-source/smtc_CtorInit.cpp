// smtc_CtorInit.cpp
//

#include "smtc_CtorInit.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_CtorInit.inl"
#endif
// semantic
#define LZZ_INLINE inline
namespace smtc
{
  CtorInit::CtorInit (util::Loc const & loc, MbrInitPtrVector const & mbr_init_set)
    : m_loc (loc), m_mbr_init_set (mbr_init_set)
    {}
}
namespace smtc
{
  CtorInit::~ CtorInit ()
    {}
}
namespace smtc
{
  util::Loc const & CtorInit::getLoc () const
    {
      return m_loc;
    }
}
#undef LZZ_INLINE
