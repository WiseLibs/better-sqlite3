// gram_TokenBlock.inl
//

// gram
#include "gram_TokenBlockImpl.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE void TokenBlock::append (basl::Token const & token) const
    {
      getTokenBlockImpl ().append (token);
    }
}
namespace gram
{
  LZZ_INLINE basl::TokenDeque const & TokenBlock::getTokens () const
    {
      return getTokenBlockImpl ().getTokens ();
    }
}
namespace gram
{
  LZZ_INLINE TokenBlockImpl & TokenBlock::getTokenBlockImpl () const
    {
      return static_cast <TokenBlockImpl &> (* getImpl ());
    }
}
#undef LZZ_INLINE
