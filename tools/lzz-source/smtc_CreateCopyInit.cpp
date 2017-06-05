// smtc_CreateCopyInit.cpp
//

#include "smtc_CreateCopyInit.h"
// semantic
#include "smtc_CopyInit.h"
#define LZZ_INLINE inline
namespace smtc
{
  InitPtr createCopyInit (util::Loc const & loc, gram::Block const & block)
  {
    return new CopyInit (loc, block);
  }
}
#undef LZZ_INLINE
