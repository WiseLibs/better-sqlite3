// gram_GetNodeCvSpecSeq.h
//

#ifndef LZZ_gram_GetNodeCvSpecSeq_h
#define LZZ_gram_GetNodeCvSpecSeq_h
// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_Cv.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::Cv getNodeCvSpecSeq (basl::Nonterm & nonterm);
}
#undef LZZ_INLINE
#endif
