// smtc_PrintMbrTmplFuncDecl.cpp
//

#include "smtc_PrintMbrTmplFuncDecl.h"
// semantic
#include "smtc_PrintTmplFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplFuncDecl (FilePtr const & file, TmplFuncDeclPtr const & tmpl_func_decl)
  {
    PrintTmplFuncDecl printer;
    printer.is_decl = true;
    printer.not_inline = true;
    // always output to declaration section
    printer.print (file, DECLARATION_SECTION, tmpl_func_decl);
  }
}
#undef LZZ_INLINE
