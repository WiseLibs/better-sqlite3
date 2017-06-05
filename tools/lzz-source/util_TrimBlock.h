// util_TrimBlock.h
//

#ifndef LZZ_util_TrimBlock_h
#define LZZ_util_TrimBlock_h
// util
#include "util_Block.h"
#define LZZ_INLINE inline
namespace util
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
#include "util_TrimBlock.inl"
#endif
#endif
