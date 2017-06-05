// smtc_GetTmplParam.cpp
//

#include "smtc_GetTmplParam.h"
// semantic
#include "smtc_CheckParamName.h"
#include "smtc_CreateTmplParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr getTmplParam (NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & def_name)
  {
    // check name
    checkParamName (name);

    // create tmpl param
    return createTmplParam (name, param_set, def_name);
  }
}
#undef LZZ_INLINE
