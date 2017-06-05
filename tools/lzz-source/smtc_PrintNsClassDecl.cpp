// smtc_PrintNsClassDecl.cpp
//

#include "smtc_PrintNsClassDecl.h"
// semantic
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsClassDecl (Output & out, ClassDeclPtr const & class_decl, NsPtr const & ns)
  {
    FilePtr const & file = isNsEnclUnmd (ns) ? out.getSrcFile () : out.getHdrFile ();
    PrintClassDecl printer;
    printer.print (file, class_decl, ns);
  }
}
#undef LZZ_INLINE
