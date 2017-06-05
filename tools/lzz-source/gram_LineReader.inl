// gram_LineReader.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE LineReader::Char::Char ()
                     {}
}
namespace gram
{
  LZZ_INLINE LineReader::Char::Char (char c, int lines, int cols)
    : c (c), lines (lines), cols (cols)
                                                                                    {}
}
namespace gram
{
  LZZ_INLINE util::Filename const & LineReader::getFilename () const
    {
      return m_filename;
    }
}
namespace gram
{
  LZZ_INLINE void LineReader::setLine (int line)
    {
      m_line = line;
    }
}
namespace gram
{
  LZZ_INLINE void LineReader::setLine (int line, util::Filename const & filename)
    {
      m_line = line;
      m_filename = filename;
    }
}
namespace gram
{
  LZZ_INLINE void LineReader::pause ()
    {
      m_char_reader.pause ();
    }
}
#undef LZZ_INLINE
