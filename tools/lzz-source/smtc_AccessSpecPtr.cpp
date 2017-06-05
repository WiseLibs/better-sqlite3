// smtc_AccessSpecPtr.cpp
//

#include "smtc_AccessSpecPtr.h"
#include "smtc_AccessSpec.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::AccessSpec>;
#undef LZZ_INLINE
