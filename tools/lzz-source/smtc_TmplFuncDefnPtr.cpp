// smtc_TmplFuncDefnPtr.cpp
//

#include "smtc_TmplFuncDefnPtr.h"
// semantic
#include "smtc_TmplFuncDefn.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::TmplFuncDefn, smtc::TmplFuncDecl>;
#undef LZZ_INLINE
