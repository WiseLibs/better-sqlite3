// smtc_PrintNsVdfClass.cpp
//

#include "smtc_PrintNsVdfClass.h"
// semantic
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintClassDefn.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintMbrDecl.h"
#include "smtc_PrintMbrDefn.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct PrintVdfClass : PrintClassDefn
  {
    void print (FilePtr const & file, ClassDefnPtr const & class_defn, NsPtr const & ns) const;
    void print (FilePtr const & file, ClassDefnPtr const & class_defn) const;
  };
}
namespace
{
  void PrintVdfClass::print (FilePtr const & file, ClassDefnPtr const & class_defn, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, class_defn);
      printNsClose (file, skind, ns_depth);
    }
}
namespace
{
  void PrintVdfClass::print (FilePtr const & file, ClassDefnPtr const & class_defn) const
    {
      printHead (file, class_defn);
      printMbrDecl (file, class_defn);
      // comment if debug
      printDir (file, skind, "#ifndef NDEBUG");
      printLine (file, skind, "char const * _cmt;");
      printDir (file, skind, "#endif");
      printCloseBrace (file, skind, true);
    }
}
namespace smtc
{
  void printNsVdfClass (Output & out, ClassDefnPtr const & class_defn, NsPtr const & ns)
  {
    // print class defn
    FilePtr const & file = isNsEnclUnmd (ns) ? out.getSrcFile () : out.getHdrFile ();
    PrintVdfClass printer;
    printer.print (file, class_defn, ns);
    // member definitions
    printMbrDefn (out, class_defn, ns);
  }
}
#undef LZZ_INLINE
