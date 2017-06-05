// util_FilenameImplPtrDataTable.h
//

#ifndef LZZ_util_FilenameImplPtrDataTable_h
#define LZZ_util_FilenameImplPtrDataTable_h
// util
#include "util_DataTable.h"
#include "util_FilenameImplPtr.h"
#define LZZ_INLINE inline
namespace util
{
  typedef DataTable <FilenameImplPtr> FilenameImplPtrDataTable;
}
namespace util
{
  typedef DataTableFindResult <FilenameImplPtr> FilenameImplPtrDataTableFindResult;
}
#undef LZZ_INLINE
#endif
