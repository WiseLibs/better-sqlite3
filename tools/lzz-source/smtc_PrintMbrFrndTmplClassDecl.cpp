// smtc_PrintMbrFrndTmplClassDecl.cpp
//

#include "smtc_PrintMbrFrndTmplClassDecl.h"
// semantic
#include "smtc_PrintTmplClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndTmplClassDecl (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl)
  {
    PrintTmplClassDecl printer;
    printer.is_frnd = true;
    printer.print (file, tmpl_class_decl);
  }
}
#undef LZZ_INLINE
