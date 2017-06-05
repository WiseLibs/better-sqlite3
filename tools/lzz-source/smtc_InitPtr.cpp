// smtc_InitPtr.cpp
//

#include "smtc_InitPtr.h"
// semantic
#include "smtc_Init.h"

// util
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Init>;
#undef LZZ_INLINE
