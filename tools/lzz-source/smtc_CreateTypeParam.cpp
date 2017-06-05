// smtc_CreateTypeParam.cpp
//

#include "smtc_CreateTypeParam.h"
// semantic
#include "smtc_TypeParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr createTypeParam (NamePtr const & name, CvType const & def_type)
  {
    return new TypeParam (name, def_type);
  }
}
#undef LZZ_INLINE
