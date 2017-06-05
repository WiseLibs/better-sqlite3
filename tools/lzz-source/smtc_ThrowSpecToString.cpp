// smtc_ThrowSpecToString.cpp
//

#include "smtc_ThrowSpecToString.h"
// semantic
#include "smtc_CvTypeSetToString.h"
#include "smtc_ThrowSpec.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String throwSpecToString (ThrowSpecPtr const & throw_spec)
  {
    util::String str = "throw";
    util::appendWithSpace (str, '(');
    str += cvTypeSetToString (throw_spec->getCvTypeSet ());
    str += ')';
    return str;
  }
}
#undef LZZ_INLINE
