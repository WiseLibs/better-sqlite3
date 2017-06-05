// smtc_TypePtr.cpp
//

#include "smtc_TypePtr.h"
#include "smtc_Type.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Type>;
#undef LZZ_INLINE
