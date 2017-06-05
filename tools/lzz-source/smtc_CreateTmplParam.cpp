// smtc_CreateTmplParam.cpp
//

#include "smtc_CreateTmplParam.h"
// semantic
#include "smtc_TmplParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr createTmplParam (NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & def_name)
  {
    return new TmplParam (name, param_set, def_name);
  }
}
#undef LZZ_INLINE
