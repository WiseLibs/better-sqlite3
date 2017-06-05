// smtc_PrintNsUsingDir.cpp
//

#include "smtc_PrintNsUsingDir.h"
// semantic
#include "smtc_Output.h"
#include "smtc_PrintUsingDir.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsUsingDir (Output & out, UsingDirPtr const & using_dir, NsPtr const & ns)
  {
    // print in source file
    printUsingDir (out.getSrcFile (), DECLARATION_SECTION, using_dir, ns);
  }
}
#undef LZZ_INLINE
