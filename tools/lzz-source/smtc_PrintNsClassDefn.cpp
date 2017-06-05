// smtc_PrintNsClassDefn.cpp
//

#include "smtc_PrintNsClassDefn.h"
// semantic
#include "smtc_ClassDefn.h"
#include "smtc_IsNameQual.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintClassDefn.h"
#include "smtc_PrintMbrDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsClassDefn (Output & out, ClassDefnPtr const & class_defn, NsPtr const & ns)
  {
    // class definition
#ifdef PRL_BUILD
    // for PRL output qualified class definitions to src file 
    FilePtr const & file = isNsEnclUnmd (ns) || isNameQual (class_defn->getName ()) ? out.getSrcFile () : out.getHdrFile ();
#else
    FilePtr const & file = isNsEnclUnmd (ns) ? out.getSrcFile () : out.getHdrFile ();
#endif

    PrintClassDefn printer;
    printer.print (file, class_defn, ns);

    // member definitions
    printMbrDefn (out, class_defn, ns);
  }
}
#undef LZZ_INLINE
