// smtc_NonTypeParamPtr.cpp
//

#include "smtc_NonTypeParamPtr.h"
// semantic
#include "smtc_NonTypeParam.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::NonTypeParam, smtc::Param>;
#undef LZZ_INLINE
