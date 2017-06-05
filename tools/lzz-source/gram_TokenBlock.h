// gram_TokenBlock.h
//

#ifndef LZZ_gram_TokenBlock_h
#define LZZ_gram_TokenBlock_h
// gram
#include "gram_Block.h"

// basil
#include "basl_TokenDeque.h"
#define LZZ_INLINE inline
namespace gram
{
  class TokenBlockImpl;
}
namespace gram
{
  class TokenBlock : public Block
  {
  public:
    TokenBlock (util::Loc const & loc);
    TokenBlock (Block const & block);
    void append (basl::Token const & token) const;
    basl::TokenDeque const & getTokens () const;
  private:
    TokenBlockImpl & getTokenBlockImpl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_TokenBlock.inl"
#endif
#endif
