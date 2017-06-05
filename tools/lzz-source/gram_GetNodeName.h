// gram_GetNodeName.h
//

#ifndef LZZ_gram_GetNodeName_h
#define LZZ_gram_GetNodeName_h
// semantic
#include "smtc_NamePtr.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::NamePtr getNodeName (basl::Nonterm & nonterm);
}
#undef LZZ_INLINE
#endif
