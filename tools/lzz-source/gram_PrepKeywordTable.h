// gram_PrepKeywordTable.h
//

#ifndef LZZ_gram_PrepKeywordTable_h
#define LZZ_gram_PrepKeywordTable_h
// util
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace gram
{
  bool isPrepKeyword (util::Ident const & name, int & kind);
}
#undef LZZ_INLINE
#endif
