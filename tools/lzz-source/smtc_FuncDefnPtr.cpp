// smtc_FuncDefnPtr.cpp
//

#include "smtc_FuncDefnPtr.h"
// semantic
#include "smtc_FuncDefn.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::FuncDefn, smtc::FuncDecl>;
#undef LZZ_INLINE
