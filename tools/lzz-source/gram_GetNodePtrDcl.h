// gram_GetNodePtrDcl.h
//

#ifndef LZZ_gram_GetNodePtrDcl_h
#define LZZ_gram_GetNodePtrDcl_h
// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace gram
{
  void getNodePtrDcl (basl::Nonterm & nonterm, smtc::CvType & cv_type);
}
#undef LZZ_INLINE
#endif
