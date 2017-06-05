// smtc_PrintNsClassInst.cpp
//

#include "smtc_PrintNsClassInst.h"
#include "conf_Config.h"
#include "smtc_ClassDecl.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsClassInst (Output & out, ClassDeclPtr const & class_decl, NsPtr const & ns)
  {
    PrintClassDecl printer;
    printer.is_inst = true;
    printer.print (out.getSrcFile (), class_decl, ns);
    if (class_decl->isDllApi () && conf::isOptionSet (conf::opt_dll_api) && ! isNsEnclUnmd (ns))
    {
      printer.is_inst_extern = true;
      printer.print (out.getHdrFile (), class_decl, ns);
    }
  }
}
#undef LZZ_INLINE
