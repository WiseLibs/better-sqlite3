// smtc_TryBlock.cpp
//

#include "smtc_TryBlock.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TryBlock.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  TryBlock::TryBlock (util::Loc const & loc, HandlerPtrVector const & handler_seq)
    : m_loc (loc), m_handler_seq (handler_seq)
    {}
}
namespace smtc
{
  TryBlock::~ TryBlock ()
    {}
}
#undef LZZ_INLINE
