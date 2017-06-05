// smtc_SpecFlagsToString.cpp
//

#include "smtc_SpecFlagsToString.h"
// semantic
#include "smtc_SpecFlags.h"

// util
#include "util_AppendWithSpace.h"
#include "util_BitOp.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct SpecName
  {
    int flag;
    char const * name;
  };
}
namespace
{
  SpecName (spec_name_set) [] =
  {
    // in output order ...
    { INLINE_SPEC,   "LZZ_INLINE" },
    { VIRTUAL_SPEC,  "virtual" },
    { EXPLICIT_SPEC, "explicit" }, 
    { STATIC_SPEC,   "static" },
    { EXTERN_SPEC,   "extern" },
    { MUTABLE_SPEC,  "mutable" },
    { AUTO_SPEC,     "auto" },
    { REGISTER_SPEC, "register" },
  };
}
namespace smtc
{
  util::String specFlagsToString (int flags)
  {
    util::String str;
    for (int i = 0; i < sizeof (spec_name_set) / sizeof (spec_name_set [0]); ++ i)
    {
      SpecName const & spec_name = spec_name_set [i];
      if (util::hasFlag (flags, spec_name.flag))
      {
        util::appendWithSpace (str, spec_name.name);
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
