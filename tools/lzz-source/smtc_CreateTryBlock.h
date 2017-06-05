// smtc_CreateTryBlock.h
//

#ifndef LZZ_smtc_CreateTryBlock_h
#define LZZ_smtc_CreateTryBlock_h
// sematnic
#include "smtc_HandlerPtrVector.h"
#include "smtc_TryBlockPtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  TryBlockPtr createTryBlock (util::Loc const & loc, HandlerPtrVector const & handler_seq);
}
#undef LZZ_INLINE
#endif
