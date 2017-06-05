// smtc_PrintMbrFrndFuncDefn.cpp
//

#include "smtc_PrintMbrFrndFuncDefn.h"
// semantic
#include "smtc_PrintFuncDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndFuncDefn (FilePtr const & file, FuncDefnPtr const & func_defn)
  {
    PrintFuncDefn printer;
    printer.is_frnd = true;
    printer.is_decl = true;
    printer.print (file, DECLARATION_SECTION, func_defn);
  }
}
#undef LZZ_INLINE
