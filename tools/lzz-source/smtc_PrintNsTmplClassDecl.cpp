// smtc_PrintNsTmplClassDecl.cpp
//

#include "smtc_PrintNsTmplClassDecl.h"
// semantic
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintTmplClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsTmplClassDecl (Output & out, TmplClassDeclPtr const & tmpl_class_decl, NsPtr const & ns)
  {
    FilePtr const & file = isNsEnclUnmd (ns) ? out.getSrcFile () : out.getHdrFile ();
    PrintTmplClassDecl printer;
    printer.print (file, tmpl_class_decl, ns);
  }
}
#undef LZZ_INLINE
