// gram_BlockImpl.cpp
//

#include "gram_BlockImpl.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_BlockImpl.inl"
#endif
#define LZZ_INLINE inline
namespace gram
{
  BlockImpl::BlockImpl (util::Loc const & loc)
    : m_loc (loc)
    {}
}
namespace gram
{
  BlockImpl::~ BlockImpl ()
    {}
}
namespace gram
{
  void BlockImpl::setLoc (util::Loc const & loc)
    {
      m_loc = loc;
    }
}
namespace gram
{
  void BlockImpl::trim ()
    {}
}
#undef LZZ_INLINE
