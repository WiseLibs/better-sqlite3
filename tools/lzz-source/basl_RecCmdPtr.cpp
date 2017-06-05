// basl_RecCmdPtr.cpp
//

#include "basl_RecCmdPtr.h"
// basil
#include "basl_RecCmd.h"

// util
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <basl::RecCmd>;
#undef LZZ_INLINE
