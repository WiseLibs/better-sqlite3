// gram_MacroPtrDataTable.h
//

#ifndef LZZ_gram_MacroPtrDataTable_h
#define LZZ_gram_MacroPtrDataTable_h
// gram
#include "gram_MacroPtr.h"

// util
#include "util_DataTable.h"
#define LZZ_INLINE inline
namespace gram
{
  typedef class util::DataTable <MacroPtr> MacroPtrDataTable;
}
namespace gram
{
  typedef class util::DataTableIter <MacroPtr> MacroPtrDataTableIter;
}
namespace gram
{
  typedef class util::DataTableFindResult <MacroPtr> MacroPtrDataTableFindResult;
}
#undef LZZ_INLINE
#endif
