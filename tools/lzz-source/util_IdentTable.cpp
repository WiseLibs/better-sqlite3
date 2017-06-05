// util_IdentTable.cpp
//

#include "util_IdentTable.h"
#define LZZ_INLINE inline
namespace util
{
  IdentTable::IdentTable ()
    {}
}
namespace util
{
  IdentTable::~ IdentTable ()
    {}
}
namespace util
{
  void IdentTable::push (char ch)
    {
      m_table.push (ch);
    }
}
namespace util
{
  void IdentTable::push (char const * str)
    {
      for (char ch = * str; ch != '\0'; ch = * ++ str)
      {
        push (ch);
      }
    }
}
namespace util
{
  Ident IdentTable::getIdent ()
    {
      return Ident (m_table.getKey ()->getData ());
    }
}
namespace util
{
  Ident IdentTable::getIdent (char const * str)
    {
      // push string then get identifier
      while (* str != 0)
      {
        push (* str ++);
      }
      return getIdent ();
    }
}
#undef LZZ_INLINE
