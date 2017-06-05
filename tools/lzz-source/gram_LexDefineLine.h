// gram_LexDefineLine.h
//

#ifndef LZZ_gram_LexDefineLine_h
#define LZZ_gram_LexDefineLine_h
// basil
#include "basl_TokenVector.h"

// util
#include "util_IdentVector.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  class Lexer;
}
namespace gram
{
  bool lexDefineLine (Lexer & lexer, bool is_cmd, util::Loc const & dir_loc, util::Loc & name_loc, util::Ident & name, bool & is_func, util::IdentVector & param_set, bool & var, basl::TokenVector & rep_set);
}
#undef LZZ_INLINE
#endif
