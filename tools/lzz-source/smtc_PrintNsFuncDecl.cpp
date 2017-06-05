// smtc_PrintNsFuncDecl.cpp
//

#include "smtc_PrintNsFuncDecl.h"
// semantic
#include "smtc_FuncDecl.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsFuncDecl (Output & out, FuncDeclPtr const & func, NsPtr const & ns)
  {
    // May 17, 2003
    // From version 2.5.2 we output function declarations to header file, not to source,
    // unless it's static or inside an unnamed namespace.  Just like function template declarations.
    // Doesn't matter if it's qualified.

    // output to file declaration section, not body
    if (func->isStatic () || isNsEnclUnmd (ns))
    {
      PrintFuncDecl printer;
      printer.is_decl = true;
      printer.print (out.getSrcFile (), DECLARATION_SECTION, func, ns);
    }
    else
    {
      PrintFuncDecl printer;
      printer.is_decl = true;
      printer.print (out.getHdrFile (), DECLARATION_SECTION, func, ns);
    }
  }
}
#undef LZZ_INLINE
