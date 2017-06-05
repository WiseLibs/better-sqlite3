// smtc_PrintMbrFrndClassDecl.cpp
//

#include "smtc_PrintMbrFrndClassDecl.h"
// semantic
#include "smtc_PrintClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndClassDecl (FilePtr const & file, ClassDeclPtr const & class_decl)
  {
    PrintClassDecl printer;
    printer.is_frnd = true;
    printer.print (file, class_decl);
  }
}
#undef LZZ_INLINE
