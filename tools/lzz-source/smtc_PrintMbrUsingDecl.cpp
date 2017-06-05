// smtc_PrintMbrUsingDecl.cpp
//

#include "smtc_PrintMbrUsingDecl.h"
// semantic
#include "smtc_PrintUsingDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrUsingDecl (FilePtr const & file, UsingDeclPtr const & using_decl)
  {
    printUsingDecl (file, DECLARATION_SECTION, using_decl);
  }
}
#undef LZZ_INLINE
