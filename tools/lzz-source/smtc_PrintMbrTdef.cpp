// smtc_PrintMbrTdef.cpp
//

#include "smtc_PrintMbrTdef.h"
// semantic
#include "smtc_PrintTdef.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTdef (FilePtr const & file, TdefPtr const & tdef)
  {
    printTdef (file, tdef);
  }
}
#undef LZZ_INLINE
