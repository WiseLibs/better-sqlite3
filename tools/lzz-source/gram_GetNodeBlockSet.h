// gram_GetNodeBlockSet.h
//

#ifndef LZZ_gram_GetNodeBlockSet_h
#define LZZ_gram_GetNodeBlockSet_h
// basil
#include "basl_Nonterm.h"

// gram
#include "gram_BlockVector.h"
#define LZZ_INLINE inline
namespace gram
{
  void getNodeBlockSet (basl::Nonterm & node, BlockVector & block_set);
}
#undef LZZ_INLINE
#endif
