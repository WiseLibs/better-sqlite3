// gram_TokenBlock.cpp
//

#include "gram_TokenBlock.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_TokenBlock.inl"
#endif
#define LZZ_INLINE inline
namespace gram
{
  TokenBlock::TokenBlock (util::Loc const & loc)
    : Block (BlockImplPtr (new TokenBlockImpl (loc)))
    {}
}
namespace gram
{
  TokenBlock::TokenBlock (Block const & block)
    : Block (block)
    {}
}
#undef LZZ_INLINE
