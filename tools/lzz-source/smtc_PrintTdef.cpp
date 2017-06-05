// smtc_PrintTdef.cpp
//

#include "smtc_PrintTdef.h"
// semantic
#include "smtc_GetNameLoc.h"
#include "smtc_NameToString.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_Tdef.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  void printTdef (FilePtr const & file, TdefPtr const & tdef, NsPtr const & ns)
  {
    int ns_depth = printNsOpen (file, DECLARATION_SECTION, ns);
    printTdef (file, tdef);
    printNsClose (file, DECLARATION_SECTION, ns_depth);
  }
}
namespace smtc
{
  void printTdef (FilePtr const & file, TdefPtr const & tdef)
  {
    String str;
    // typedefs can have linkage
    Linkage const & linkage = tdef->getLinkage ();
    if (linkage.isSet ())
    {
      appendWithSpace (str, "extern");
      appendWithSpace (str, linkage.getLanguage ().c_str ());
    }
    appendWithSpace (str, "typedef");
    String dcl_str = nameToString (tdef->getName ());
    appendWithSpace (str, tdef->getCvType ().toString (dcl_str));
    str += ';';
    Loc loc = getNameLoc (tdef->getName ());
    printLine (file, DECLARATION_SECTION, loc, str);
  }
}
#undef LZZ_INLINE
