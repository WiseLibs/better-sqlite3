// smtc_HandlerPtr.cpp
//

#include "smtc_HandlerPtr.h"
#include "smtc_Handler.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Handler>;
#undef LZZ_INLINE
