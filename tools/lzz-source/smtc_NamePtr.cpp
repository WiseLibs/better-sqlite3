// smtc_NamePtr.cpp
//

#include "smtc_NamePtr.h"
#include "smtc_Name.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Name>;
#undef LZZ_INLINE
