// util_FilenameImplPtr.cpp
//

#include "util_FilenameImplPtr.h"
#include "util_FilenameImpl.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <util::FilenameImpl>;
#undef LZZ_INLINE
