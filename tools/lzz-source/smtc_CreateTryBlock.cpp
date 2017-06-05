// smtc_CreateTryBlock.cpp
//

#include "smtc_CreateTryBlock.h"
// semantic
#include "smtc_TryBlock.h"
#define LZZ_INLINE inline
namespace smtc
{
  TryBlockPtr createTryBlock (util::Loc const & loc, HandlerPtrVector const & handler_seq)
  {
    return new TryBlock (loc, handler_seq);
  }
}
#undef LZZ_INLINE
