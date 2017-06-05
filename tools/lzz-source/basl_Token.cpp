// basl_Token.cpp
//

#include "basl_Token.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_Token.inl"
#endif
#define LZZ_INLINE inline
namespace basl
{
  Token::~ Token ()
    {}
}
namespace basl
{
  int Token::getNumber () const
    {
      return m_number;
    }
}
namespace basl
{
  void Token::setNumber (int number)
    {
      m_number = number;
    }
}
namespace basl
{
  util::Ident const & Token::getLexeme () const
    {
      return m_lexeme;
    }
}
namespace basl
{
  void Token::setLexeme (util::Ident const & lexeme)
    {
      m_lexeme = lexeme;
    }
}
namespace basl
{
  util::Loc const & Token::getLoc () const
    {
      return m_loc;
    }
}
namespace basl
{
  void Token::setLoc (util::Loc const & loc)
    {
      m_loc = loc;
    }
}
#undef LZZ_INLINE
