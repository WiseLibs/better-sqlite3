// smtc_FilePtr.cpp
//

#include "smtc_FilePtr.h"
#include "smtc_File.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::File>;
#undef LZZ_INLINE
