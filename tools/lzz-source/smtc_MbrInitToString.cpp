// smtc_MbrInitToString.cpp
//

#include "smtc_MbrInitToString.h"
// semantic
#include "smtc_MbrInit.h"
#include "smtc_NameToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  util::String mbrInitToString (MbrInitPtr const & mbr_init)
  {
    String str = nameToString (mbr_init->getName ());
    appendWithSpace (str, '(');
    str += mbr_init->getArgSet ();
    str += ')';
    return str;
  }
}
#undef LZZ_INLINE
