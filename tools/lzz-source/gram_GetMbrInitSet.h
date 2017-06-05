// gram_GetMbrInitSet.h
//

#ifndef LZZ_gram_GetMbrInitSet_h
#define LZZ_gram_GetMbrInitSet_h
// semantic
#include "smtc_MbrInitPtrVector.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  void getMbrInitSet (basl::Nonterm & nonterm, smtc::MbrInitPtrVector & mbr_init_set);
}
#undef LZZ_INLINE
#endif
