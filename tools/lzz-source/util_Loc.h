// util_Loc.h
//

#ifndef LZZ_util_Loc_h
#define LZZ_util_Loc_h
// util
#include "util_Filename.h"
#define LZZ_INLINE inline
namespace util
{
  class Loc
  {
    Filename m_filename;
    unsigned short int m_line;
    unsigned short int m_column;
  public:
    Loc ();
    Loc (Filename const & filename, unsigned short int line, unsigned short int column);
    ~ Loc ();
    bool isSet () const;
    Filename const & getFilename () const;
    int getLine () const;
    int getColumn () const;
  };
}
namespace util
{
  bool operator < (Loc const & a, Loc const & b);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "util_Loc.inl"
#endif
#endif
