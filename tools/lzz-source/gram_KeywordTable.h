// gram_KeywordTable.h
//

#ifndef LZZ_gram_KeywordTable_h
#define LZZ_gram_KeywordTable_h
// util
#include "util_Ident.h"
#include "util_IntDataTable.h"
#define LZZ_INLINE inline
namespace gram
{
  bool isKeyword (util::Ident const & lexeme, int & kind);
}
#undef LZZ_INLINE
#endif
