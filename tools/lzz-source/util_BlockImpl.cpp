// util_BlockImpl.cpp
//

#include "util_BlockImpl.h"
#ifndef LZZ_ENABLE_INLINE
#include "util_BlockImpl.inl"
#endif
// std lib
#include <cstdlib>
#include <cctype>
#include <cstring>
#define LZZ_INLINE inline
namespace util
{
  BlockImpl::BlockImpl (Loc const & loc)
    : m_loc (loc), m_size (32), m_length (0), m_num_lines (0)
    {
      m_data = (char *) malloc (m_size);
      m_data [0] = '\0';
    }
}
namespace util
{
  BlockImpl::~ BlockImpl ()
    {
      free (m_data);
    }
}
namespace util
{
  void BlockImpl::setLoc (Loc const & loc)
    {
      m_loc = loc;
    }
}
namespace util
{
  void BlockImpl::append (char ch)
    {
      if (m_length + 1 == m_size)
      {
        m_size *= 2;
        m_data = (char *) realloc (m_data, m_size);
      }
      m_data [m_length] = ch;
      m_data [++ m_length] = '\0';
      if (ch == '\n')
      {
        m_num_lines ++;
      }
    }
}
namespace util
{
  void BlockImpl::append (char const * str)
    {
      for (char const * s = str; * s != '\0'; ++ s)
      {
        append (* s);
      }
    }
}
namespace util
{
  void BlockImpl::freeze ()
    {
      // free unused memory
      m_size = m_length + 1;
      m_data = (char *) realloc (m_data, m_size);
    }
}
namespace util
{
  void BlockImpl::trim ()
    {
      char * s = m_data;
      while (* s && isspace (* s))
      {
        if (* s == '\n')
        {
          -- m_num_lines;
        }
        ++ s;
      }
      if (s != m_data)
      {
        m_length -= s - m_data;
        memmove (m_data, s, m_length);
      }
      s = m_data + m_length - 1;
      while (s >= m_data && isspace (* s))
      {
        if (* s == '\n')
        {
          -- m_num_lines;
        }
        -- s;
      }
      m_length = s + 1 - m_data; 
      * (s + 1) = '\0';
      // free excess memory
      freeze ();
    }
}
namespace util
{
  bool BlockImpl::isEmpty () const
    {
      for (char * s = m_data; * s != '\0'; ++ s)
      {
        if (! isspace (* s))
        {
          return false;
        }
      }
      return true;
    }
}
#undef LZZ_INLINE
