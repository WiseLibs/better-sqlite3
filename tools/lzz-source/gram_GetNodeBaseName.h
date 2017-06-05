// gram_GetNodeBaseName.h
//

#ifndef LZZ_gram_GetNodeBaseName_h
#define LZZ_gram_GetNodeBaseName_h
// semantic
#include "smtc_BaseNamePtr.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::BaseNamePtr getNodeBaseName (basl::Nonterm & nonterm);
}
#undef LZZ_INLINE
#endif
