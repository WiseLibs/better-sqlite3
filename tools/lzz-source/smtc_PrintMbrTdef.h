// smtc_PrintMbrTdef.h
//

#ifndef LZZ_smtc_PrintMbrTdef_h
#define LZZ_smtc_PrintMbrTdef_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_TdefPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printMbrTdef (FilePtr const & file, TdefPtr const & tdef);
}
#undef LZZ_INLINE
#endif
