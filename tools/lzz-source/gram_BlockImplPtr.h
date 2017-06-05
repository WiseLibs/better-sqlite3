// gram_BlockImplPtr.h
//

#ifndef LZZ_gram_BlockImplPtr_h
#define LZZ_gram_BlockImplPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  class BlockImpl;
}
namespace gram
{
  typedef util::BPtr <BlockImpl> BlockImplPtr;
}
#undef LZZ_INLINE
#endif
