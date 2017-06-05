// smtc_SetReturnStmt.h
//

#ifndef LZZ_smtc_SetReturnStmt_h
#define LZZ_smtc_SetReturnStmt_h
// semantic
#include "smtc_ScopePtr.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  void setReturnStmt (ScopePtr const & cs, gram::Block const & stmt);
}
#undef LZZ_INLINE
#endif
