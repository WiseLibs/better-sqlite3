// gram_CharBlockImpl.cpp
//

#include "gram_CharBlockImpl.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_CharBlockImpl.inl"
#endif
// std lib
#include <cstdlib>
#include <cctype>
#include <cstring>
#define LZZ_INLINE inline
namespace gram
{
  CharBlockImpl::CharBlockImpl (util::Loc const & loc)
    : BlockImpl (loc), m_size (INITSIZE), m_length (0), m_num_lines (0)
    {
      m_data = (char *) malloc (m_size);
      m_data [0] = '\0';
    }
}
namespace gram
{
  CharBlockImpl::~ CharBlockImpl ()
    {
      free (m_data);
    }
}
namespace gram
{
  bool CharBlockImpl::isCharBlock () const
    {
      return true;
    }
}
namespace gram
{
  util::String CharBlockImpl::toString () const
    {
      return m_data;
    }
}
namespace gram
{
  void CharBlockImpl::append (char ch)
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
namespace gram
{
  void CharBlockImpl::append (char const * str)
    {
      for (char const * s = str; * s != '\0'; ++ s)
      {
        append (* s);
      }
    }
}
namespace gram
{
  void CharBlockImpl::freeze ()
    {
      // free unused memory
      m_size = m_length + 1;
      m_data = (char *) realloc (m_data, m_size);
    }
}
namespace gram
{
  void CharBlockImpl::trim ()
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
namespace gram
{
  bool CharBlockImpl::isEmpty () const
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
