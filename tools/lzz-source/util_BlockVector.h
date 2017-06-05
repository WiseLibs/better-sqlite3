// util_BlockVector.h
//

#ifndef LZZ_util_BlockVector_h
#define LZZ_util_BlockVector_h
#include <vector>
#include "util_Block.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::vector <Block> BlockVector;
}
namespace util
{
  typedef std::vector <Block>::iterator BlockVectorIter;
}
namespace util
{
  typedef std::vector <Block>::const_iterator BlockVectorConstIter;
}
#undef LZZ_INLINE
#endif
