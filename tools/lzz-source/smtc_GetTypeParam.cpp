// smtc_GetTypeParam.cpp
//

#include "smtc_GetTypeParam.h"
// semantic
#include "smtc_CheckParamName.h"
#include "smtc_CreateTypeParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr getTypeParam (NamePtr const & name, CvType const & def_type)
  {
    // check name
    checkParamName (name);
    
    // create type param
    return createTypeParam (name, def_type);
  }
}
#undef LZZ_INLINE
