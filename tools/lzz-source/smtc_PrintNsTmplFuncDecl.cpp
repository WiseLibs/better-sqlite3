// smtc_PrintNsTmplFuncDecl.cpp
//

#include "smtc_PrintNsTmplFuncDecl.h"
// semantic
#include "smtc_FuncDecl.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintTmplFuncDecl.h"
#include "smtc_TmplFuncDecl.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct Printer
  {
    TmplFuncDeclPtr const & tmpl_func_decl;
    NsPtr const & ns;
    void printDecl (FilePtr const & file);
  public:
    explicit Printer (TmplFuncDeclPtr const & tmpl_func_decl, NsPtr const & ns);
    ~ Printer ();
  };
}
namespace
{
  void Printer::printDecl (FilePtr const & file)
    {
      PrintTmplFuncDecl printer;
      printer.is_decl = true;
      printer.print (file, DECLARATION_SECTION, tmpl_func_decl, ns);
    }
}
namespace
{
  LZZ_INLINE Printer::Printer (TmplFuncDeclPtr const & tmpl_func_decl, NsPtr const & ns)
    : tmpl_func_decl (tmpl_func_decl), ns (ns)
         {}
}
namespace
{
  Printer::~ Printer ()
         {}
}
namespace smtc
{
  void printNsTmplFuncDecl (Output & out, TmplFuncDeclPtr const & tmpl_func_decl, NsPtr const & ns)
  {
    // May 17, 2003
    // From version 2.5.2 we output function template declarations to header file, not to source,
    // unless it's static or inside an unnamed namespace.  Just like function declarations.

    // Doesn't matter if qualified; output to declaration section, like function declaration
    Printer printer (tmpl_func_decl, ns);
    FuncDeclPtr func = tmpl_func_decl->getFuncDecl ();
    if (func->isStatic () || isNsEnclUnmd (ns))
    {
      // source file
      printer.printDecl (out.getSrcFile ());
    }
    else
    {
      // otherwise header
      printer.printDecl (out.getHdrFile ());
    }
  }
}
#undef LZZ_INLINE
