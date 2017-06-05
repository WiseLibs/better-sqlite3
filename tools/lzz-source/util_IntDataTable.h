// util_IntDataTable.h
//

#ifndef LZZ_util_IntDataTable_h
#define LZZ_util_IntDataTable_h
// lib
#include <stddef.h>

// util
#include "util_DataTable.h"
#define LZZ_INLINE inline
namespace util
{
  typedef DataTable <size_t> IntDataTable;
}
namespace util
{
  typedef DataTableFindResult <size_t> IntDataTableFindResult;
}
#undef LZZ_INLINE
#endif
