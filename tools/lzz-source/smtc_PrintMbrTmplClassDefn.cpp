// smtc_PrintMbrTmplClassDefn.cpp
//

#include "smtc_PrintMbrTmplClassDefn.h"
// semantic
#include "smtc_PrintTmplClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplClassDefn (FilePtr const & file, TmplClassDefnPtr const & tmpl_class_defn)
  {
    PrintTmplClassDefn printer;
    printer.print (file, tmpl_class_defn);
  }
}
#undef LZZ_INLINE
