// util_CharPtrDataTable.h
//

#ifndef LZZ_util_CharPtrDataTable_h
#define LZZ_util_CharPtrDataTable_h
// lib
#include <stddef.h>

// util
#include "util_DataTable.h"
#define LZZ_INLINE inline
namespace util
{
  typedef DataTable <char const *> CharPtrDataTable;
}
namespace util
{
  typedef DataTableFindResult <char const *> CharPtrDataTableFindResult;
}
#undef LZZ_INLINE
#endif
