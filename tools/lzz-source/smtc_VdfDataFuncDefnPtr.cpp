// smtc_VdfDataFuncDefnPtr.cpp
//

#include "smtc_VdfDataFuncDefnPtr.h"
// semantic
#include "smtc_VdfDataFuncDefn.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::VdfDataFuncDefn, smtc::FuncDecl>;
#undef LZZ_INLINE
