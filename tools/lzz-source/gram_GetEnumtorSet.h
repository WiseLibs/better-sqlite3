// gram_GetEnumtorSet.h
//

#ifndef LZZ_gram_GetEnumtorSet_h
#define LZZ_gram_GetEnumtorSet_h
// semantic
#include "smtc_EnumtorPtrVector.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  void getEnumtorSet (basl::Nonterm & nonterm, smtc::EnumtorPtrVector & enumtor_set);
}
#undef LZZ_INLINE
#endif
