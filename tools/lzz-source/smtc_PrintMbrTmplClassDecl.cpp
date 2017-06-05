// smtc_PrintMbrTmplClassDecl.cpp
//

#include "smtc_PrintMbrTmplClassDecl.h"
// semantic
#include "smtc_PrintTmplClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplClassDecl (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl)
  {
    PrintTmplClassDecl printer;
    printer.print (file, tmpl_class_decl);
  }
}
#undef LZZ_INLINE
