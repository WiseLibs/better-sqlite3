// gram_EvalHashIfExpr.h
//

#ifndef LZZ_gram_EvalHashIfExpr_h
#define LZZ_gram_EvalHashIfExpr_h
// gram
#include "basl_TokenDeque.h"
#define LZZ_INLINE inline
namespace gram
{
  bool evalHashIfExpr (util::Ident const & dir_name, util::Loc const & eol_loc, basl::TokenDeque const & in_set);
}
#undef LZZ_INLINE
#endif
