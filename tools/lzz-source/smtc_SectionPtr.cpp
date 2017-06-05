// smtc_SectionPtr.cpp
//

#include "smtc_SectionPtr.h"
#include "smtc_Section.h"
#include "util_BPtr.tpl"
#define LZZ_INLINE inline
template class util::BPtr <smtc::Section>;
#undef LZZ_INLINE
