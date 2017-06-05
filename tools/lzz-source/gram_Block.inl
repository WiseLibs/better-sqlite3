// gram_Block.inl
//

#include "gram_BlockImpl.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE bool Block::isSet () const
    {
      return impl.isSet ();
    }
}
namespace gram
{
  LZZ_INLINE bool Block::isCharBlock () const
    {
      return impl->isCharBlock ();
    }
}
namespace gram
{
  LZZ_INLINE bool Block::isTokenBlock () const
    {
      return impl->isTokenBlock ();
    }
}
namespace gram
{
  LZZ_INLINE util::Loc const & Block::getLoc () const
    {
      return impl->getLoc ();
    }
}
namespace gram
{
  LZZ_INLINE void Block::trim () const
    {
      impl->trim ();
    }
}
namespace gram
{
  LZZ_INLINE bool Block::isEmpty () const
    {
      return impl->isEmpty ();
    }
}
namespace gram
{
  LZZ_INLINE util::String Block::toString () const
    {
      return impl->toString ();
    }
}
namespace gram
{
  LZZ_INLINE void TrimBlock::operator () (Block const & block) const
  {
    block.trim ();
  }
}
namespace gram
{
  LZZ_INLINE TrimBlock::TrimBlock ()
              {}
}
#undef LZZ_INLINE
