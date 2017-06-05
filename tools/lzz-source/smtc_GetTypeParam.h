// smtc_GetTypeParam.h
//

#ifndef LZZ_smtc_GetTypeParam_h
#define LZZ_smtc_GetTypeParam_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr getTypeParam (NamePtr const & name, CvType const & def_type);
}
#undef LZZ_INLINE
#endif
