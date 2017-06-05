// smtc_PrintMbrFrndTmplFuncDefn.cpp
//

#include "smtc_PrintMbrFrndTmplFuncDefn.h"
// semantic
#include "smtc_PrintTmplFuncDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndTmplFuncDefn (FilePtr const & file, TmplFuncDefnPtr const & tmpl_func_defn)
  {
    // print to file
    PrintTmplFuncDefn printer;
    printer.is_frnd = true;
    printer.is_decl = true;
    printer.print (file, DECLARATION_SECTION, tmpl_func_defn);
  }
}
#undef LZZ_INLINE
