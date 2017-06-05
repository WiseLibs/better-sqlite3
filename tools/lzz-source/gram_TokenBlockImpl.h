// gram_TokenBlockImpl.h
//

#ifndef LZZ_gram_TokenBlockImpl_h
#define LZZ_gram_TokenBlockImpl_h
// gram
#include "gram_BlockImpl.h"

// basil
#include "basl_TokenDeque.h"
#define LZZ_INLINE inline
namespace gram
{
  class TokenBlockImpl : public BlockImpl
  {
    basl::TokenDeque m_tokens;
  public:
    TokenBlockImpl (util::Loc const & loc);
    ~ TokenBlockImpl ();
    bool isCharBlock () const;
    bool isEmpty () const;
    util::String toString () const;
    void append (basl::Token const & token);
    basl::TokenDeque const & getTokens () const;
  };
}
#undef LZZ_INLINE
#endif
