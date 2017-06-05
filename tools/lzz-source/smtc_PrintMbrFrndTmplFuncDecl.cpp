// smtc_PrintMbrFrndTmplFuncDecl.cpp
//

#include "smtc_PrintMbrFrndTmplFuncDecl.h"
// semantic
#include "smtc_PrintTmplFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndTmplFuncDecl (FilePtr const & file, TmplFuncDeclPtr const & tmpl_func_decl)
  {
    PrintTmplFuncDecl printer;
    printer.is_frnd = true;
    printer.is_decl = true;
    printer.not_inline = true;
    printer.print (file, DECLARATION_SECTION, tmpl_func_decl);
  }
}
#undef LZZ_INLINE
