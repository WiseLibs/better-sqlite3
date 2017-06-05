// smtc_NavSubmitFuncDefnPtr.cpp
//

#include "smtc_NavSubmitFuncDefnPtr.h"
// semantic
#include "smtc_NavSubmitFuncDefn.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::NavSubmitFuncDefn, smtc::FuncDecl>;
#undef LZZ_INLINE
