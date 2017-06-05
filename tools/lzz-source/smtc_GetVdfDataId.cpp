// smtc_GetVdfDataId.cpp
//

#include "smtc_GetVdfDataId.h"
// std lib
#include <cctype>

// semantic
#include "util_IntToString.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String getVdfDataId (util::String const & vdf_type, util::String const & str)
  {
    // result string is vdf type followed by encoded string
    util::String res_str = vdf_type;
    res_str += '_';
    for (char const * s = str.c_str (); * s != '\0'; ++ s)
    {
      char ch = * s;
      if (! isspace (ch))
      {
        if (! isalnum (ch))
        {
          res_str += util::intToString (ch);
        }
        else
        {
          res_str += ch;
        }
      }
    }
    return res_str;
  }
}
#undef LZZ_INLINE
