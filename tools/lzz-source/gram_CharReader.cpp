// gram_CharReader.cpp
//

#include "gram_CharReader.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_CharReader.inl"
#endif
// std lib
#include <cstdlib>
#include <cstring>

// gram
#include "gram_IsHexDigit.h"
#include "gram_Message.h"

// util
#include "util_Exception.h"

// config
#include "conf_Config.h"
#define LZZ_INLINE inline
namespace gram
{
  using namespace msg;
}
namespace gram
{
  using namespace util;
}
namespace gram
{
  CharReader::CharReader (util::Filename const & filename)
    : m_file_reader (filename), m_column (1), m_peek_beg (0), m_peek_end (0)
    {}
}
namespace gram
{
  CharReader::CharReader (util::String const & str, util::Loc const & loc)
    : m_file_reader (str, loc), m_column (loc.getColumn ()), m_peek_beg (0), m_peek_end (0)
    {}
}
namespace gram
{
  bool CharReader::peekChar (char & c, int n)
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
  bool CharReader::readChar (char & c, int & cols)
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
      cols = ch.cols;
      return true;
    }
}
namespace gram
{
  bool CharReader::readDirectChar (Char & ch)
    {
      char c;
      if (! m_file_reader.readChar (c))
      {
        return false;
      }
      int cols = 1;
      // check if trigraph
      if (c == '?')
      {
        char c1, c2;
        if (m_file_reader.peekChar (c1, 0) && c1 == '?' && m_file_reader.peekChar (c2, 1))
        {
          const char * p = strchr ("=/'()!<>-" "\0" "#\\^[]|{}~", c2);
          if (p != 0)
          {
            m_file_reader.readChar (c1);
            m_file_reader.readChar (c2);
            c = p [10];
            cols += 2;
          }
        }
      }
      // convert '\r\n' to '\n' for dos end of line
      else if (c == '\r')
      {
        char c1;
        if (m_file_reader.peekChar (c1, 0) && c1 == '\n')
        {
          m_file_reader.readChar (c);
          cols = 2;
        }
      }
      // check for tab
      else if (c == '\t')
      {
        int tab_stop = conf::getOptionValue (conf::opt_tab_stop);
        cols = tab_stop - (m_column - 1) % tab_stop;
      }
      if (c == '\n')
      {
        m_column = 1;
      }
      else
      {
        m_column += cols;
      }
      ch = Char (c, cols);
      return true;
    }
}
#undef LZZ_INLINE
