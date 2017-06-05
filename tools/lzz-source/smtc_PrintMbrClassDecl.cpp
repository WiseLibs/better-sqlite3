// smtc_PrintMbrClassDecl.cpp
//

#include "smtc_PrintMbrClassDecl.h"
// semantic
#include "smtc_PrintClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrClassDecl (FilePtr const & file, ClassDeclPtr const & class_decl)
  {
    PrintClassDecl printer;
    printer.print (file, class_decl);
  }
}
#undef LZZ_INLINE
