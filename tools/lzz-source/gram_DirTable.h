// gram_DirTable.h
//

#ifndef LZZ_gram_DirTable_h
#define LZZ_gram_DirTable_h
// gram
#include "gram_DirKind.h"

// util
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace gram
{
  bool isDir (util::Ident const & name, DirKind & kind);
}
#undef LZZ_INLINE
#endif
