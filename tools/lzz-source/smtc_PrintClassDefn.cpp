// smtc_PrintClassDefn.cpp
//

#include "smtc_PrintClassDefn.h"
// semantic
#include "smtc_BaseSpecSetToString.h"
#include "smtc_ClassDefn.h"
#include "smtc_GetNameLoc.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintMbrDecl.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  void PrintClassDefn::print (FilePtr const & file, ClassDefnPtr const & class_defn, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, class_defn);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintClassDefn::print (FilePtr const & file, ClassDefnPtr const & class_defn) const
    {
      printHead (file, class_defn);
      printMbrDecl (file, class_defn);
      printCloseBrace (file, skind, true);
    }
}
namespace smtc
{
  void PrintClassDefn::printHead (FilePtr const & file, ClassDefnPtr const & class_defn) const
    {
      String str = declToString (class_defn);
      BaseSpecPtrVector const & base_spec_set = class_defn->getBaseSpecSet ();
      if (! base_spec_set.empty ())
      {
        appendWithSpace (str, ':');
        appendWithSpace (str, baseSpecSetToString (base_spec_set));
      }
      printLine (file, skind, getNameLoc (class_defn->getName ()), str);
      printOpenBrace (file, skind);
    }
}
#undef LZZ_INLINE
