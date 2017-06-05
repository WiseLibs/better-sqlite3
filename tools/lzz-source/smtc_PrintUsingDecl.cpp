// smtc_PrintUsingDecl.cpp
//

#include "smtc_PrintUsingDecl.h"
// semantic
#include "smtc_GetNameLoc.h"
#include "smtc_NameToString.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_UsingDecl.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printUsingDecl (FilePtr const & file, SectionKind skind, UsingDeclPtr const & using_decl, NsPtr const & ns)
  {
    int ns_depth = printNsOpen (file, skind, ns);
    printUsingDecl (file, skind, using_decl);
    printNsClose (file, skind, ns_depth);
  }
}
namespace smtc
{
  void printUsingDecl (FilePtr const & file, SectionKind skind, UsingDeclPtr const & using_decl)
  {
    using namespace util;
    String str = "using";
    NamePtr const & name = using_decl->getName ();
    appendWithSpace (str, nameToString (name));
    str += ';';
    printLine (file, skind, getNameLoc (name), str);
  }
}
#undef LZZ_INLINE
