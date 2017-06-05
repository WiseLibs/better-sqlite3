// smtc_PrintMbrFuncDecl.cpp
//

#include "smtc_PrintMbrFuncDecl.h"
// semantic
#include "smtc_PrintFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFuncDecl (FilePtr const & file, FuncDeclPtr const & func_decl)
  {
    PrintFuncDecl printer;
    printer.is_decl = true;
    printer.not_inline = true;
    // class definitions are always output to declaration section
    printer.print (file, DECLARATION_SECTION, func_decl);
  }
}
#undef LZZ_INLINE
