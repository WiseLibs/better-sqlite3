// gram_CSPrep.cpp
//

#include "gram_CSPrep.h"
// gram
#include "gram_LexBlockToken.h"
#define LZZ_INLINE inline
namespace gram
{
  CSPrep::CSPrep (util::String const & name, smtc::Output * output, bool insert_all)
    : m_prep (name, output, insert_all)
    {}
}
namespace gram
{
  CSPrep::CSPrep (util::String const & str, util::Loc const & loc)
    : m_prep (str, loc)
    {}
}
namespace gram
{
  basl::Token CSPrep::getNextToken (int lex_state)
    {
      basl::Token token;
      if (lex_state == 0 || ! lexBlockToken (m_prep, lex_state, token))
      {
        token = m_prep.getNextToken ();
      }
      return token;
    }
}
#undef LZZ_INLINE
