// smtc_TmplClassDefnPtr.cpp
//

#include "smtc_TmplClassDefnPtr.h"
// semantic
#include "smtc_TmplClassDefn.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::TmplClassDefn, smtc::TmplClassDecl>;
#undef LZZ_INLINE
