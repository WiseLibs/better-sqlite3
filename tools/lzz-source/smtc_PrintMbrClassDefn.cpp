// smtc_PrintMbrClassDefn.cpp
//

#include "smtc_PrintMbrClassDefn.h"
// semantic
#include "smtc_PrintClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrClassDefn (FilePtr const & file, ClassDefnPtr const & class_defn)
  {
    PrintClassDefn printer;
    printer.print (file, class_defn);
  }
}
#undef LZZ_INLINE
