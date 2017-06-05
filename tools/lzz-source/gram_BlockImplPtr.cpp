// gram_BlockImplPtr.cpp
//

#include "gram_BlockImplPtr.h"
#include "gram_BlockImpl.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <gram::BlockImpl>;
#undef LZZ_INLINE
