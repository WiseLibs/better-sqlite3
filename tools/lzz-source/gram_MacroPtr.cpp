// gram_MacroPtr.cpp
//

#include "gram_MacroPtr.h"
#include "gram_Macro.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <gram::Macro>;
#undef LZZ_INLINE
