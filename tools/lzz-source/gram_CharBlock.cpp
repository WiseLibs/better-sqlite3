// gram_CharBlock.cpp
//

#include "gram_CharBlock.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_CharBlock.inl"
#endif
#define LZZ_INLINE inline
namespace gram
{
  CharBlock::CharBlock (util::Loc const & loc)
    : Block (BlockImplPtr (new CharBlockImpl (loc)))
    {}
}
namespace gram
{
  CharBlock::CharBlock (Block const & block)
    : Block (block)
    {}
}
#undef LZZ_INLINE
