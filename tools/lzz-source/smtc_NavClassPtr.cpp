// smtc_NavClassPtr.cpp
//

#include "smtc_NavClassPtr.h"
// semantic
#include "smtc_NavClass.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::NavClass, smtc::ClassDecl>;
#undef LZZ_INLINE
