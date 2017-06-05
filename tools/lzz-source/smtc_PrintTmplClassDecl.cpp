// smtc_PrintTmplClassDecl.cpp
//

#include "smtc_PrintTmplClassDecl.h"
// semantic
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_PrintTmplSpecSet.h"
#include "smtc_TmplClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void PrintTmplClassDecl::print (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, DECLARATION_SECTION, ns);
      print (file, tmpl_class_decl);
      printNsClose (file, DECLARATION_SECTION, ns_depth);
    }
}
namespace smtc
{
  void PrintTmplClassDecl::print (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl) const
    {
      printTmplSpecSet (file, DECLARATION_SECTION, tmpl_class_decl->getTmplSpecSet (), true);
      PrintClassDecl::print (file, tmpl_class_decl->getClassDecl ());
    }
}
#undef LZZ_INLINE
