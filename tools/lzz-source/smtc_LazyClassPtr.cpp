// smtc_LazyClassPtr.cpp
//

#include "smtc_LazyClassPtr.h"
// semantic
#include "smtc_LazyClass.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::LazyClass, smtc::ClassDecl>;
#undef LZZ_INLINE
