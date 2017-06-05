// basl_AttribPtr.cpp
//

#include "basl_AttribPtr.h"
// basil
#include "basl_Attrib.h"

// util
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <basl::Attrib>;
#undef LZZ_INLINE
