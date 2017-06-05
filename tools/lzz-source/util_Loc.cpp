// util_Loc.cpp
//

#include "util_Loc.h"
#ifndef LZZ_ENABLE_INLINE
#include "util_Loc.inl"
#endif
#include <cstring>
#define LZZ_INLINE inline
namespace util
{
  Loc::Loc ()
    : m_line (0), m_column (1)
    {}
}
namespace util
{
  Loc::Loc (Filename const & filename, unsigned short int line, unsigned short int column)
    : m_filename (filename), m_line (line), m_column (column)
    {}
}
namespace util
{
  Loc::~ Loc ()
    {}
}
namespace util
{
  bool operator < (Loc const & a, Loc const & b)
  {
    bool result = false;
    if (a.getFilename () == b.getFilename ())
    {
      if (a.getLine () < b.getLine ())
      {
        result = true;
      }
      else if (a.getLine () == b.getLine ())
      {
        result = a.getColumn () < b.getColumn ();
      }
    }
    else
    {
      result = a.getFilename () < b.getFilename ();
    }
    return result;
  }
}
#undef LZZ_INLINE
