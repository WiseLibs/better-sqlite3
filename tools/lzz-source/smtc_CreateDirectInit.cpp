// smtc_CreateDirectInit.cpp
//

#include "smtc_CreateDirectInit.h"
// semantic
#include "smtc_DirectInit.h"
#define LZZ_INLINE inline
namespace smtc
{
  InitPtr createDirectInit (util::Loc const & loc, gram::BlockVector const & block_set)
  {
    return new DirectInit (loc, block_set);
  }
}
#undef LZZ_INLINE
