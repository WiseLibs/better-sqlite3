// smtc_GetFuncParam.h
//

#ifndef LZZ_smtc_GetFuncParam_h
#define LZZ_smtc_GetFuncParam_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtr.h"

// gram
#include "gram_SpecSel.h"

// util
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr getFuncParam (gram::SpecSel const & spec_sel, CvType const & cv_type, NamePtr const & name, gram::Block const & def_arg);
}
#undef LZZ_INLINE
#endif
