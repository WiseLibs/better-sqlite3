// gram_BlockVector.h
//

#ifndef LZZ_gram_BlockVector_h
#define LZZ_gram_BlockVector_h
#include <vector>
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace gram
{
  typedef std::vector <Block> BlockVector;
}
namespace gram
{
  typedef std::vector <Block>::iterator BlockVectorIter;
}
namespace gram
{
  typedef std::vector <Block>::const_iterator BlockVectorConstIter;
}
#undef LZZ_INLINE
#endif
