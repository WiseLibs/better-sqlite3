// smtc_PrintTmplClassDefn.cpp
//

#include "smtc_PrintTmplClassDefn.h"
// semantic
#include "smtc_PrintClassDefn.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_PrintTmplSpecSet.h"
#include "smtc_TmplClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void PrintTmplClassDefn::print (FilePtr const & file, TmplClassDefnPtr const & tmpl_class_defn, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, DECLARATION_SECTION, ns);
      print (file, tmpl_class_defn);
      printNsClose (file, DECLARATION_SECTION, ns_depth);
    }
}
namespace smtc
{
  void PrintTmplClassDefn::print (FilePtr const & file, TmplClassDefnPtr const & tmpl_class_defn) const
    {
      printTmplSpecSet (file, DECLARATION_SECTION, tmpl_class_defn->getTmplSpecSet (), true);
      PrintClassDefn::print (file, tmpl_class_defn->getClassDefn ());
    }
}
#undef LZZ_INLINE
