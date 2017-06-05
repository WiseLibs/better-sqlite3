// smtc_CreateHandler.h
//

#ifndef LZZ_smtc_CreateHandler_h
#define LZZ_smtc_CreateHandler_h
// semantic
#include "smtc_HandlerPtr.h"
#include "smtc_ParamPtr.h"

// gram
#include "gram_Block.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  HandlerPtr createHandler (util::Loc const & loc, ParamPtr const & catch_decl, gram::Block const & body);
}
#undef LZZ_INLINE
#endif
