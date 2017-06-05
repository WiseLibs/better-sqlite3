// gram_Block.cpp
//

#include "gram_Block.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_Block.inl"
#endif
#define LZZ_INLINE inline
namespace gram
{
  Block::Block ()
    {}
}
namespace gram
{
  Block::Block (BlockImplPtr const & impl)
    : impl (impl)
    {}
}
namespace gram
{
  Block::~ Block ()
    {}
}
namespace gram
{
  void Block::setLoc (util::Loc const & loc)
    {
      impl->setLoc (loc);
    }
}
namespace gram
{
  BlockImplPtr const & Block::getImpl () const
    {
      return impl;
    }
}
namespace gram
{
  TrimBlock::~ TrimBlock ()
              {}
}
#undef LZZ_INLINE
