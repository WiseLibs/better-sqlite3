// smtc_ObjPtr.cpp
//

#include "smtc_ObjPtr.h"
#include "smtc_Obj.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Obj>;
#undef LZZ_INLINE
