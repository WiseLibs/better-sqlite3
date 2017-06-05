// gram_PrepFile.h
//

#ifndef LZZ_gram_PrepFile_h
#define LZZ_gram_PrepFile_h
// basil
#include "basl_TokenDeque.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  void prepFile (util::String const & filename, bool insert_all, basl::TokenDeque & token_set);
}
#undef LZZ_INLINE
#endif
