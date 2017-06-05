// smtc_BaseSpecToString.cpp
//

#include "smtc_BaseSpecToString.h"
// semantic
#include "smtc_AccessToString.h"
#include "smtc_BaseSpec.h"
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
  util::String baseSpecToString (BaseSpecPtr const & base_spec)
  {
    String str;
    if (base_spec->isVirtual ())
    {
      str = "virtual";
    }
    appendWithSpace (str, accessToString (base_spec->getAccess ()));
    appendWithSpace (str, nameToString (base_spec->getBaseName ()));
    return str;
  }
}
#undef LZZ_INLINE
