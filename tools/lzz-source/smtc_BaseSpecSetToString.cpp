// smtc_BaseSpecSetToString.cpp
//

#include "smtc_BaseSpecSetToString.h"
// semantic
#include "smtc_BaseSpecToString.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  util::String baseSpecSetToString (BaseSpecPtrVector const & base_spec_set)
  {
    String str;
    for (BaseSpecPtrVectorConstIter i = base_spec_set.begin (); i != base_spec_set.end (); ++ i)
    {
      str += baseSpecToString (* i);
      if (i + 1 != base_spec_set.end ())
      {
        str += ", ";
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
