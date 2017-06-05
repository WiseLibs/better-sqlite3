// smtc_PrintNsTmplClassDefn.cpp
//

#include "smtc_PrintNsTmplClassDefn.h"
// semantic
#include "smtc_IsExplicitTmplSpec.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintMbrDefn.h"
#include "smtc_PrintTmplClassDefn.h"
#include "smtc_PrintTmplMbrDefn.h"
#include "smtc_TmplClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsTmplClassDefn (Output & out, TmplClassDefnPtr const & tmpl_class_defn, NsPtr const & ns)
  {
    // class definition (and member declarations)
    FilePtr const & file = isNsEnclUnmd (ns) ? out.getSrcFile () : out.getHdrFile ();
    PrintTmplClassDefn printer;
    printer.print (file, tmpl_class_defn, ns);

    // if explicit specialization then we don't print 'template <>' before definitions
    TmplSpecPtrVector const & tmpl_spec_set = tmpl_class_defn->getTmplSpecSet ();
    if (isExplicitTmplSpec (tmpl_spec_set))
    {
      printMbrDefn (out, tmpl_class_defn->getClassDefn (), ns);
    }
    else
    {
      // precede defintions with tmpl spec set
      printTmplMbrDefn (out, tmpl_class_defn, ns);
    }
  }
}
#undef LZZ_INLINE
