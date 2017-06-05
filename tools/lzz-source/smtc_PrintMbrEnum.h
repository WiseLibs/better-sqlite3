// smtc_PrintMbrEnum.h
//

#ifndef LZZ_smtc_PrintMbrEnum_h
#define LZZ_smtc_PrintMbrEnum_h
// semantic
#include "smtc_EnumPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrEnum (FilePtr const & file, EnumPtr const & en);
}
#undef LZZ_INLINE
#endif
