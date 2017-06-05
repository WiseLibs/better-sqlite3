// smtc_MbrInitSetToString.cpp
//

#include "smtc_MbrInitSetToString.h"
// semantic
#include "smtc_MbrInitToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  util::String mbrInitSetToString (MbrInitPtrVector const & mbr_init_set)
  {
    String str;
    for (MbrInitPtrVectorConstIter beg = mbr_init_set.begin (), end = mbr_init_set.end (); beg != end; ++ beg)
    {
      MbrInitPtr const & mbr_init = * beg;
      appendWithSpace (str, mbrInitToString (mbr_init));
      if (beg + 1 != end)
      {
        str += ',';
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
