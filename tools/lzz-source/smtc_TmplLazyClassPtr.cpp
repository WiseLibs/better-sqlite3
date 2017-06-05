// smtc_TmplLazyClassPtr.cpp
//

#include "smtc_TmplLazyClassPtr.h"
// semantic
#include "smtc_TmplLazyClass.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::TmplLazyClass, smtc::TmplClassDecl>;
#undef LZZ_INLINE
