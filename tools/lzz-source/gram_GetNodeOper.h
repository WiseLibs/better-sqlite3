// gram_GetNodeOper.h
//

#ifndef LZZ_gram_GetNodeOper_h
#define LZZ_gram_GetNodeOper_h
// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_OperKind.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::OperKind getNodeOper (basl::Nonterm & nonterm);
}
#undef LZZ_INLINE
#endif
