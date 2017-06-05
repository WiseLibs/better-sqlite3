// smtc_AppendCv.cpp
//

#include "smtc_AppendCv.h"
// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  void appendCv (util::String & str, bool c, bool v)
  {
    if (c)
    {
      util::appendWithSpace (str, "const");
    }
    if (v)
    {
      util::appendWithSpace (str, "volatile");
    }
  }
}
namespace smtc
{
  void appendCv (util::String & str, Cv const & cv)
  {
    appendCv (str, cv.isConst (), cv.isVolatile ());
  }
}
#undef LZZ_INLINE
