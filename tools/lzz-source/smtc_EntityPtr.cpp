// smtc_EntityPtr.cpp
//

#include "smtc_EntityPtr.h"
#include "smtc_Entity.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Entity>;
#undef LZZ_INLINE
