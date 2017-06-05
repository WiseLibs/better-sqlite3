// gram_TokenBlockImpl.cpp
//

#include "gram_TokenBlockImpl.h"
// std lib
#include <algorithm>

// util
#include "gram_PrettyPrintTokens.h"
#define LZZ_INLINE inline
namespace gram
{
  TokenBlockImpl::TokenBlockImpl (util::Loc const & loc)
    : BlockImpl (loc)
    {}
}
namespace gram
{
  TokenBlockImpl::~ TokenBlockImpl ()
    {}
}
namespace gram
{
  bool TokenBlockImpl::isCharBlock () const
    {
      return false;
    }
}
namespace gram
{
  bool TokenBlockImpl::isEmpty () const
    {
      return m_tokens.empty ();
    }
}
namespace gram
{
  util::String TokenBlockImpl::toString () const
    {
      return prettyPrintTokensToString (m_tokens);
    }
}
namespace gram
{
  void TokenBlockImpl::append (basl::Token const & token)
    {
      m_tokens.push_back (token);
    }
}
namespace gram
{
  basl::TokenDeque const & TokenBlockImpl::getTokens () const
    {
      return m_tokens;
    }
}
#undef LZZ_INLINE
