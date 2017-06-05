// smtc_PrintNsUsingDecl.cpp
//

#include "smtc_PrintNsUsingDecl.h"
// semantic
#include "smtc_Output.h"
#include "smtc_PrintUsingDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsUsingDecl (Output & out, UsingDeclPtr const & using_decl, NsPtr const & ns)
  {
    // always print in source file (similar to an extern declaration)
    printUsingDecl (out.getSrcFile (), DECLARATION_SECTION, using_decl, ns);
  }
}
#undef LZZ_INLINE
