// smtc_TryBlockPtr.cpp
//

#include "smtc_TryBlockPtr.h"
#include "smtc_TryBlock.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::TryBlock>;
#undef LZZ_INLINE
