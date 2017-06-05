// smtc_CtorInitToString.cpp
//

#include "smtc_CtorInitToString.h"
// semantic
#include "smtc_CtorInit.h"
#include "smtc_MbrInitSetToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  util::String ctorInitToString (CtorInitPtr const & ctor_init)
  {
    String str = ":";
    appendWithSpace (str, mbrInitSetToString (ctor_init->getMbrInitSet ()));
    return str;
  }
}
#undef LZZ_INLINE
