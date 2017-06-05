// smtc_CvTypeSetToString.cpp
//

#include "smtc_CvTypeSetToString.h"
// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String cvTypeSetToString (CvTypeVector const & cv_type_set)
  {
    util::String str;
    if (! cv_type_set.empty ())
    {
      for (CvTypeVectorConstIter i = cv_type_set.begin ();;)
      {
        util::appendWithSpace (str, i->toString ());
        if (++ i == cv_type_set.end ())
        {
          break;
        }
        str += ',';
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
