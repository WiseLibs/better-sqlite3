// smtc_ParamSetToString.cpp
//

#include "smtc_ParamSetToString.h"
// semantic
#include "smtc_Param.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String paramSetToString (ParamPtrVector const & param_set, bool is_decl)
  {
    using namespace util;
    String str;
    for (ParamPtrVectorConstIter i = param_set.begin (); i != param_set.end (); ++ i)
    {
      appendWithSpace (str, (* i)->toString (is_decl));
      if (i + 1 != param_set.end ())
      {
        str += ',';
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
