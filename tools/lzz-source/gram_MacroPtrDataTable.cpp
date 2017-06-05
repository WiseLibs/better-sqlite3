// gram_MacroPtrDataTable.cpp
//

#include "gram_MacroPtrDataTable.h"
// util
#include "util_DataTable.tpl"
#define LZZ_INLINE inline
template class util::DataTableNode <gram::MacroPtr>;
template class util::DataTableFindResult <gram::MacroPtr>;
template class util::DataTable <gram::MacroPtr>;
template class util::DataTableIter <gram::MacroPtr>;
#undef LZZ_INLINE
