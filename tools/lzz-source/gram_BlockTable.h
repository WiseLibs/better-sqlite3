// gram_BlockTable.h
//

#ifndef LZZ_gram_BlockTable_h
#define LZZ_gram_BlockTable_h
#include "gram_Block.h"
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  util::Ident addBlock (Block const & block);
}
namespace gram
{
  Block getBlock (util::Ident const & lexeme);
}
#undef LZZ_INLINE
#endif
