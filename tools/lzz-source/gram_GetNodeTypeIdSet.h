// gram_GetNodeTypeIdSet.h
//

#ifndef LZZ_gram_GetNodeTypeIdSet_h
#define LZZ_gram_GetNodeTypeIdSet_h
// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_CvTypeVector.h"
#define LZZ_INLINE inline
namespace gram
{
  void getNodeTypeIdSet (basl::Nonterm & nonterm, smtc::CvTypeVector & cv_type_set);
}
#undef LZZ_INLINE
#endif
