// smtc_GetCatchParam.h
//

#ifndef LZZ_smtc_GetCatchParam_h
#define LZZ_smtc_GetCatchParam_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_NonTypeParamPtr.h"

// gram
#include "gram_SpecSel.h"
#define LZZ_INLINE inline
namespace smtc
{
  NonTypeParamPtr getCatchParam (gram::SpecSel const & spec_sel, CvType const & cv_type, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
