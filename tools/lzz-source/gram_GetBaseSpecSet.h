// gram_GetBaseSpecSet.h
//

#ifndef LZZ_gram_GetBaseSpecSet_h
#define LZZ_gram_GetBaseSpecSet_h
// semantic
#include "smtc_BaseSpecPtrVector.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  void getBaseSpecSet (basl::Nonterm & nonterm, smtc::BaseSpecPtrVector & base_spec_set);
}
#undef LZZ_INLINE
#endif
