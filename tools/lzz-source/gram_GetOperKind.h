// gram_GetOperKind.h
//

#ifndef LZZ_gram_GetOperKind_h
#define LZZ_gram_GetOperKind_h
// semantic
#include "smtc_OperKind.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::OperKind getOperKind (int number);
}
#undef LZZ_INLINE
#endif
