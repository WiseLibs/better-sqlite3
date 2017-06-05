// gram_GetNodeInit.h
//

#ifndef LZZ_gram_GetNodeInit_h
#define LZZ_gram_GetNodeInit_h
// semantic
#include "smtc_InitPtr.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::InitPtr getNodeInit (basl::Nonterm & nonterm);
}
#undef LZZ_INLINE
#endif
