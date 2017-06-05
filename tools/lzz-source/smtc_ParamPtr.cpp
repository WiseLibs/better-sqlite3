// smtc_ParamPtr.cpp
//

#include "smtc_ParamPtr.h"
#include "smtc_Param.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Param>;
#undef LZZ_INLINE
