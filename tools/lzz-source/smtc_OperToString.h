// smtc_OperToString.h
//

#ifndef LZZ_smtc_OperToString_h
#define LZZ_smtc_OperToString_h
// semantic
#include "smtc_OperKind.h"
#define LZZ_INLINE inline
namespace smtc
{
  char const * operToString (OperKind oper);
}
#undef LZZ_INLINE
#endif
