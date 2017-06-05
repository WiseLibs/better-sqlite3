// smtc_CreateNonTypeParam.h
//

#ifndef LZZ_smtc_CreateNonTypeParam_h
#define LZZ_smtc_CreateNonTypeParam_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NonTypeParamPtr.h"
#include "smtc_Param.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  NonTypeParamPtr createNonTypeParam (int flags, CvType const & cv_type, NamePtr const & name, gram::Block const & def_arg);
}
#undef LZZ_INLINE
#endif
