// util_BlockMap.h
//

#ifndef LZZ_util_BlockMap_h
#define LZZ_util_BlockMap_h
// std lib
#include <map>

// util
#include "util_Block.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::map <Loc, Block> BlockMap;
}
#undef LZZ_INLINE
#endif
