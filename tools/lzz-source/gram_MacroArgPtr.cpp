// gram_MacroArgPtr.cpp
//

#include "gram_MacroArgPtr.h"
#include "gram_MacroArg.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <gram::MacroArg>;
#undef LZZ_INLINE
