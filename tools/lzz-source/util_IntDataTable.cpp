// util_IntDataTable.cpp
//

#include "util_IntDataTable.h"
// util
#include "util_DataTable.tpl"
#define LZZ_INLINE inline
namespace util
{
  template class DataTable <size_t>;
}
namespace util
{
  template class DataTableNode <size_t>;
}
namespace util
{
  template class DataTableIter <size_t>;
}
namespace util
{
  template class DataTableFindResult <size_t>;
}
#undef LZZ_INLINE
