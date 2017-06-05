// smtc_PrintNsUsingDir.h
//

#ifndef LZZ_smtc_PrintNsUsingDir_h
#define LZZ_smtc_PrintNsUsingDir_h
// semantic
#include "smtc_UsingDirPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsUsingDir (Output & out, UsingDirPtr const & using_dir, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
