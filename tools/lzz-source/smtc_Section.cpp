// smtc_Section.cpp
//

#include "smtc_Section.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Section.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  Section::Section (SectionKind kind)
    : m_kind (kind), m_indent (0)
    {}
}
namespace smtc
{
  Section::~ Section ()
    {}
}
namespace smtc
{
  SectionKind Section::getKind () const
    {
      return m_kind;
    }
}
namespace smtc
{
  std::ostream & Section::indent (int offset)
    {
      return indentExactly ((m_indent + offset) * 2);
    }
}
namespace smtc
{
  std::ostream & Section::indentExactly (int num)
    {
      enum { MAX_INDENT = 512 };
      static char buf [MAX_INDENT];
      if (num > MAX_INDENT - 1)
      {
        num = MAX_INDENT - 1;
      }
      memset (buf, ' ', num);
      buf [num] = '\0';
      m_os << buf;
      return m_os;
    }
}
namespace smtc
{
  void Section::incIndent ()
    {
      ++ m_indent;
    }
}
namespace smtc
{
  void Section::decIndent ()
    {
      assert (m_indent > 0);
      -- m_indent;
    }
}
namespace smtc
{
  void Section::freeze ()
    {
      m_os.freeze ();
    }
}
namespace smtc
{
  char const * Section::freeze (int & size)
    {
      m_os.freeze ();
      size = m_os.pcount ();
      return m_os.str ();
    }
}
namespace smtc
{
  char const * Section::toString (int & size)
    {
      size = m_os.pcount ();
      return m_os.str ();
    }
}
#undef LZZ_INLINE
