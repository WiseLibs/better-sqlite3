// gram_CSPrep.h
//

#ifndef LZZ_gram_CSPrep_h
#define LZZ_gram_CSPrep_h
// gram
#include "gram_Prep.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  class CSPrep
  {
    Prep m_prep;
  public:
    CSPrep (util::String const & name, smtc::Output * output, bool insert_all = false);
    CSPrep (util::String const & str, util::Loc const & loc);
    basl::Token getNextToken (int lex_state);
  };
}
#undef LZZ_INLINE
#endif
