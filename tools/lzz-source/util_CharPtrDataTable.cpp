// util_CharPtrDataTable.cpp
//

#include "util_CharPtrDataTable.h"
// util
#include "util_DataTable.tpl"
#define LZZ_INLINE inline
namespace util
{
  template class DataTable <char const *>;
}
namespace util
{
  template class DataTableNode <char const *>;
}
namespace util
{
  template class DataTableIter <char const *>;
}
namespace util
{
  template class DataTableFindResult <char const *>;
}
#undef LZZ_INLINE
