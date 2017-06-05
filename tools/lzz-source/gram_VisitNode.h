// gram_VisitNode.h
//

#ifndef LZZ_gram_VisitNode_h
#define LZZ_gram_VisitNode_h
// semantic
#include "smtc_ScopePtrDeque.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  void visitNode (basl::Nonterm & nonterm, smtc::ScopePtrDeque & ss);
}
#undef LZZ_INLINE
#endif
