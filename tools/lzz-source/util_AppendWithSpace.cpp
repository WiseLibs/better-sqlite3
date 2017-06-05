// util_AppendWithSpace.cpp
//

#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace util
{
  void appendWithSpace (util::String & str1, util::String const & str2)
  {
    if (! str2.empty ())
    {
      if (! str1.empty ())
      {
        str1 += ' ';
      }
      str1 += str2;
    }
  }
}
namespace util
{
  void appendWithSpace (util::String & str1, char const * str2)
  {
    if (str2 [0] != '\0')
    {
      if (! str1.empty ())
      {
        str1 += ' ';
      }
      str1 += str2;
    }
  }
}
namespace util
{
  void appendWithSpace (util::String & str1, char ch)
  {
    if (ch != ' ')
    {
      if (! str1.empty ())
      {
        str1 += ' ';
      }
      str1 += ch;
    }
  }
}
#undef LZZ_INLINE
