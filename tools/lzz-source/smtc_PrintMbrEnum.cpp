// smtc_PrintMbrEnum.cpp
//

#include "smtc_PrintMbrEnum.h"
// semantic
#include "smtc_PrintEnum.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrEnum (FilePtr const & file, EnumPtr const & en)
  {
    printEnum (file, en);
  }
}
#undef LZZ_INLINE
