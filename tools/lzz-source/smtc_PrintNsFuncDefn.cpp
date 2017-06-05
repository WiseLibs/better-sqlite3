// smtc_PrintNsFuncDefn.cpp
//

#include "smtc_PrintNsFuncDefn.h"
// semantic
#include "smtc_FuncDefn.h"
#include "smtc_IsNameQual.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintFuncDefn.h"

// config
#include "conf_Config.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct Printer
  {
    FuncDefnPtr const & func_defn;
    NsPtr const & ns;
    bool is_decl;
    void printDecl (FilePtr const & file);
    void printDefn (FilePtr const & file, SectionKind skind = BODY_SECTION);
  public:
    explicit Printer (FuncDefnPtr const & func_defn, NsPtr const & ns);
    ~ Printer ();
  };
}
namespace
{
  void Printer::printDecl (FilePtr const & file)
    {
      PrintFuncDecl printer;
      printer.is_decl = is_decl;
      printer.not_inline = true;
      printer.print (file, DECLARATION_SECTION, func_defn, ns);
      is_decl = false;
    }
}
namespace
{
  void Printer::printDefn (FilePtr const & file, SectionKind skind)
    {
      PrintFuncDefn printer;
      printer.is_decl = is_decl;
      printer.print (file, skind, func_defn, ns);
    }
}
namespace
{
  LZZ_INLINE Printer::Printer (FuncDefnPtr const & func_defn, NsPtr const & ns)
    : func_defn (func_defn), ns (ns), is_decl (true)
         {}
}
namespace
{
  Printer::~ Printer ()
         {}
}
namespace smtc
{
  void printNsFuncDefn (Output & out, FuncDefnPtr const & func_defn, NsPtr const & ns)
  {
    Printer printer (func_defn, ns);
    bool is_qual = isNameQual (func_defn->getName ());
    if (func_defn->isStatic () || isNsEnclUnmd (ns))
    {
      if (! is_qual)
      {
        printer.printDecl (out.getSrcFile ());
      }
      printer.printDefn (out.getSrcFile ());
    }
    else
    {
      if (! is_qual)
      {
        printer.printDecl (out.getHdrFile ());
      }
      if (func_defn->isInline ())
      {
        if (conf::getOptionValue (conf::opt_inl_inl))
        {
          printer.printDefn (out.getHdrFile (), INLINE_BODY_SECTION);
          printer.printDefn (out.getSrcFile (), INLINE_BODY_SECTION);
        }
        else if (conf::getOptionValue (conf::opt_inl))
        {
          printer.printDefn (out.getInlFile ());
        }
        else
        {
          printer.printDefn (out.getHdrFile ());
        }
      }
      else
      {
        printer.printDefn (out.getSrcFile ());
      }
    }
  }
}
#undef LZZ_INLINE
