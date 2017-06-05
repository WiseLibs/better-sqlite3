// basl_Token.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE Token::Token ()
    : m_flags (0)
    {}
}
namespace basl
{
  LZZ_INLINE Token::Token (int number, util::Loc const & loc, util::Ident const & lexeme)
    : m_flags (IS_SET_TOKEN), m_number (number), m_loc (loc), m_lexeme (lexeme)
    {}
}
namespace basl
{
  LZZ_INLINE bool Token::isSet () const
    {
      return m_flags & IS_SET_TOKEN;
    }
}
namespace basl
{
  LZZ_INLINE void Token::setSpaceBefore ()
    {
      m_flags |= SPACE_BEFORE_TOKEN;
    }
}
namespace basl
{
  LZZ_INLINE bool Token::hasSpaceBefore () const
    {
      return m_flags & SPACE_BEFORE_TOKEN;
    }
}
namespace basl
{
  LZZ_INLINE void Token::setRecSubMacro ()
    {
      m_flags |= REC_SUB_MACRO_TOKEN;
    }
}
namespace basl
{
  LZZ_INLINE bool Token::isRecSubMacro () const
    {
      return m_flags & REC_SUB_MACRO_TOKEN;
    }
}
namespace basl
{
  LZZ_INLINE bool Token::fromMacro () const
    {
      return m_flags & FROM_MACRO_TOKEN;
    }
}
namespace basl
{
  LZZ_INLINE void Token::setFromMacro ()
    {
      m_flags |= FROM_MACRO_TOKEN;
    }
}
#undef LZZ_INLINE
