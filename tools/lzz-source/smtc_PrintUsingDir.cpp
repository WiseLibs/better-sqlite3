// smtc_PrintUsingDir.cpp
//

#include "smtc_PrintUsingDir.h"
// semantic
#include "smtc_GetNameLoc.h"
#include "smtc_NameToString.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_UsingDir.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printUsingDir (FilePtr const & file, SectionKind skind, UsingDirPtr const & using_dir, NsPtr const & ns)
  {
    int ns_depth = printNsOpen (file, skind, ns);
    printUsingDir (file, skind, using_dir);
    printNsClose (file, skind, ns_depth);
  }
}
namespace smtc
{
  void printUsingDir (FilePtr const & file, SectionKind skind, UsingDirPtr const & using_dir)
  {
    using namespace util;
    String str = "using namespace";
    NamePtr const & name = using_dir->getName ();
    appendWithSpace (str, nameToString (name));
    str += ';';
    printLine (file, skind, getNameLoc (name), str);
  }
}
#undef LZZ_INLINE
