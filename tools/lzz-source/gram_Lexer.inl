// gram_Lexer.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE bool Lexer::fromFile () const
    {
      return ! fromString ();
    }
}
namespace gram
{
  LZZ_INLINE bool Lexer::peekChar (char & ch, int n)
    {
      return m_reader.peekChar (ch, n);
    }
}
namespace gram
{
  LZZ_INLINE bool Lexer::readChar (char & ch)
    {
      return m_reader.readChar (ch);
    }
}
namespace gram
{
  LZZ_INLINE bool Lexer::getNextToken (basl::Token & token)
    {
      util::Loc loc;
      return getNextToken (NORMAL_LEX_STATE, loc, token);
    }
}
namespace gram
{
  LZZ_INLINE bool Lexer::getNextToken (util::Loc & loc, basl::Token & token)
    {
      return getNextToken (NORMAL_LEX_STATE, loc, token);
    }
}
namespace gram
{
  LZZ_INLINE bool Lexer::getNextToken (LexState lex_state, basl::Token & token)
    {
      util::Loc loc;
      return getNextToken (lex_state, loc, token);
    }
}
namespace gram
{
  LZZ_INLINE util::Filename const & Lexer::getFilename () const
    {
      return m_reader.getFilename ();
    }
}
namespace gram
{
  LZZ_INLINE void Lexer::setLine (int line)
    {
      m_reader.setLine (line);
    }
}
namespace gram
{
  LZZ_INLINE void Lexer::setLine (int line, util::Filename const & filename)
    {
      m_reader.setLine (line, filename);
    }
}
namespace gram
{
  LZZ_INLINE void Lexer::pause ()
    {
      m_reader.pause ();
    }
}
#undef LZZ_INLINE
