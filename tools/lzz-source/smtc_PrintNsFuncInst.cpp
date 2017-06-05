// smtc_PrintNsFuncInst.cpp
//

#include "smtc_PrintNsFuncInst.h"
// semantic
#include "smtc_PrintFuncDecl.h"
#include "smtc_Output.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsFuncInst (Output & out, FuncDeclPtr const & func_decl, NsPtr const & ns)
  {
    PrintFuncDecl printer;
    printer.is_inst = true;
    printer.print (out.getSrcFile (), BODY_SECTION, func_decl, ns);
  }
}
#undef LZZ_INLINE
