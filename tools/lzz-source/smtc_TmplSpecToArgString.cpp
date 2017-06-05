// smtc_TmplSpecToArgString.cpp
//

#include "smtc_TmplSpecToArgString.h"
// semantic
#include "smtc_NameToString.h"
#include "smtc_Param.h"
#include "smtc_TmplSpec.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  util::String tmplSpecToArgString (TmplSpecPtr const & tmpl_spec)
  {
    String str;
    ParamPtrVector const & param_set = tmpl_spec->getParamSet ();
    for (ParamPtrVectorConstIter beg = param_set.begin (), end = param_set.end (); beg != end; ++ beg)
    {
      ParamPtr const & param = * beg;
      appendWithSpace (str, nameToString (param->getName ()));
      if (beg + 1 != end)
      {
        str += ',';
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
