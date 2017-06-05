// smtc_PrintMbrFrndFuncDecl.cpp
//

#include "smtc_PrintMbrFrndFuncDecl.h"
// semantic
#include "smtc_PrintFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndFuncDecl (FilePtr const & file, FuncDeclPtr const & func_decl)
  {
    PrintFuncDecl printer;
    printer.is_frnd = true;
    printer.is_decl = true;
    printer.not_inline = true;
    printer.print (file, DECLARATION_SECTION, func_decl);
  }
}
#undef LZZ_INLINE
