// gram_LineReader.cpp
//

#include "gram_LineReader.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_LineReader.inl"
#endif
// gram
#define LZZ_INLINE inline
namespace gram
{
  using namespace util;
}
namespace gram
{
  LineReader::LineReader (util::Filename const & filename)
    : m_char_reader (filename), m_peek_beg (0), m_peek_end (0), m_filename (filename), m_line (1), m_column (1), m_newline (true)
    {}
}
namespace gram
{
  LineReader::LineReader (util::String const & str, util::Loc const & loc)
    : m_char_reader (str, loc), m_peek_beg (0), m_peek_end (0), m_filename (loc.getFilename ()), m_line (loc.getLine ()), m_column (loc.getColumn ()), m_newline (true)
    {}
}
namespace gram
{
  bool LineReader::peekChar (char & c, int n)
    {
      int i = (m_peek_beg + n) % MAX_PEEK;
      if (i == m_peek_end)
      {
        if (! readDirectChar (m_peek_buf [m_peek_end]))
        {
          return false;
        }
        m_peek_end = (m_peek_end + 1) % MAX_PEEK;
      }
      c = m_peek_buf [i].c; 
      return true;
    }
}
namespace gram
{
  bool LineReader::readChar (char & c)
    {
      // check in peek buffer first
      Char ch;
      if (m_peek_beg == m_peek_end)
      {
        if (! readDirectChar (ch))
        {
          return false;
        }
      }
      else
      {
        ch = m_peek_buf [m_peek_beg];
        m_peek_beg = (m_peek_beg + 1) % MAX_PEEK;
      }
      c = ch.c;
      if (ch.lines > 0)
      {
        m_line += ch.lines;
        m_column = 1;
      }
      else
      {
        m_column += ch.cols;
      }
      return true;
    }
}
namespace gram
{
  util::Loc LineReader::getLocation () const
    {
      return Loc (m_filename, m_line, m_column);
    }
}
namespace gram
{
  bool LineReader::readDirectChar (Char & ch)
    {
      char c;
      int cols;
      int lines = 0;
      for (;;)
      {
        if (! m_char_reader.readChar (c, cols))
        {
          // want newline before end of file
          if (m_newline)
          {
            return false;
          }
          c = '\n';
        }
        else
        {
          // check if backslash followed by newline
          char c1;
          if (c == '\\' && m_char_reader.peekChar (c1, 0) && c1 == '\n')
          {
            m_char_reader.readChar (c, cols);
            ++ lines;
            continue;
          }
        }
        break;
      }
      if (c == '\n')
      {
        ++ lines;
        m_newline = true;
      }
      else
      {
        m_newline = false;
      }
      ch = Char (c, lines, cols);
      return true;
    }
}
#undef LZZ_INLINE
