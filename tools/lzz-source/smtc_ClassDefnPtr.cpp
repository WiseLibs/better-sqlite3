// smtc_ClassDefnPtr.cpp
//

#include "smtc_ClassDefnPtr.h"
// semantic
#include "smtc_ClassDefn.h"

// util
#include "util_DPtr.tpl"
#define LZZ_INLINE inline
template class util::DPtr <smtc::ClassDefn, smtc::ClassDecl>;
#undef LZZ_INLINE
