// smtc_UsingDeclPtr.cpp
//

#include "smtc_UsingDeclPtr.h"
#include "smtc_UsingDecl.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::UsingDecl>;
#undef LZZ_INLINE
