// util_FilenameImplPtrDataTable.cpp
//

#include "util_FilenameImplPtrDataTable.h"
// util
#include "util_DataTable.tpl"
#define LZZ_INLINE inline
namespace util
{
  template class DataTable <FilenameImplPtr>;
}
namespace util
{
  template class DataTableNode <FilenameImplPtr>;
}
namespace util
{
  template class DataTableIter <FilenameImplPtr>;
}
namespace util
{
  template class DataTableFindResult <FilenameImplPtr>;
}
#undef LZZ_INLINE
