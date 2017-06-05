// gram_GetHandlerSet.h
//

#ifndef LZZ_gram_GetHandlerSet_h
#define LZZ_gram_GetHandlerSet_h
// semantic
#include "smtc_HandlerPtrVector.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  void getHandlerSet (basl::Nonterm & nonterm, smtc::HandlerPtrVector & handler_set);
}
#undef LZZ_INLINE
#endif
