// smtc_EnumPtr.cpp
//

#include "smtc_EnumPtr.h"
#include "smtc_Enum.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Enum>;
#undef LZZ_INLINE
