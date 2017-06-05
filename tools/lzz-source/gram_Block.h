// gram_Block.h
//

#ifndef LZZ_gram_Block_h
#define LZZ_gram_Block_h
// gram
#include "gram_BlockImplPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  class Loc;
}
namespace gram
{
  class Block
  {
    BlockImplPtr impl;
  public:
    Block ();
    Block (BlockImplPtr const & impl);
    ~ Block ();
    bool isSet () const;
    bool isCharBlock () const;
    bool isTokenBlock () const;
    void setLoc (util::Loc const & loc);
    util::Loc const & getLoc () const;
    void trim () const;
    bool isEmpty () const;
    util::String toString () const;
  protected:
    BlockImplPtr const & getImpl () const;
  };
}
namespace gram
{
  struct TrimBlock
  {
    void operator () (Block const & block) const;
  public:
    explicit TrimBlock ();
    ~ TrimBlock ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_Block.inl"
#endif
#endif
