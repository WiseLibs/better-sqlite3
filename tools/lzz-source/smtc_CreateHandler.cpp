// smtc_CreateHandler.cpp
//

#include "smtc_CreateHandler.h"
// semantic
#include "smtc_Handler.h"
#define LZZ_INLINE inline
namespace smtc
{
  HandlerPtr createHandler (util::Loc const & loc, ParamPtr const & catch_decl, gram::Block const & body)
  {
    return new Handler (loc, catch_decl, body);
  }
}
#undef LZZ_INLINE
