// smtc_PrintNsTmplFuncDefn.cpp
//

#include "smtc_PrintNsTmplFuncDefn.h"
// semantic
#include "smtc_FuncDecl.h"
#include "smtc_IsExplicitTmplSpec.h"
#include "smtc_IsNameQual.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintTmplFuncDecl.h"
#include "smtc_PrintTmplFuncDefn.h"
#include "smtc_TmplFuncDefn.h"

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
    TmplFuncDefnPtr const & tmpl_func_defn;
    NsPtr const & ns;
    bool is_decl;
    void printDecl (FilePtr const & file);
    void printDefn (FilePtr const & file, SectionKind skind = BODY_SECTION);
  public:
    explicit Printer (TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns);
    ~ Printer ();
  };
}
namespace
{
  void Printer::printDecl (FilePtr const & file)
    {
      PrintTmplFuncDecl printer;
      printer.is_decl = is_decl;
      printer.not_inline = true;
      printer.print (file, DECLARATION_SECTION, tmpl_func_defn, ns);
      is_decl = false;
    }
}
namespace
{
  void Printer::printDefn (FilePtr const & file, SectionKind skind)
    {
      PrintTmplFuncDefn printer;
      printer.is_decl = is_decl;
      printer.print (file, skind, tmpl_func_defn, ns);
    }
}
namespace
{
  LZZ_INLINE Printer::Printer (TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns)
    : tmpl_func_defn (tmpl_func_defn), ns (ns), is_decl (true)
         {}
}
namespace
{
  Printer::~ Printer ()
         {}
}
namespace smtc
{
  void printNsTmplFuncDefn (Output & out, TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns)
  {
    Printer printer (tmpl_func_defn, ns);
    FuncDeclPtr const & func_decl = tmpl_func_defn->getFuncDecl ();
    /* we don't care if it's qualified, we want to output declarations in any case
    bool is_qual = isNameQual (func_decl->getName ());
    */
    // we want to do the same thing as an explicit spec if we're outputting tpl code to source
    bool is_expl_spec = isExplicitTmplSpec (tmpl_func_defn->getTmplSpecSet ()) || conf::getOptionValue (conf::opt_tpl_src);
    if (func_decl->isStatic () || isNsEnclUnmd (ns))
    {
      /*
      if (! is_qual)
      {
        printer.printDecl (out.getSrcFile ());
      }
      */
      printer.printDecl (out.getSrcFile ());
      printer.printDefn (out.getSrcFile ());
    }
    else
    {
      /*
      if (! is_qual)
      {
        printer.printDecl (out.getHdrFile ());
      }
      */
      printer.printDecl (out.getHdrFile ());
      if (func_decl->isInline ())
      {
        if (is_expl_spec)
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
        else if (conf::getOptionValue (conf::opt_tnl))
        {
          printer.printDefn (out.getTnlFile ());
        }
        else
        {
          printer.printDefn (out.getHdrFile ());
        }
      }
      else if (is_expl_spec)
      {
        printer.printDefn (out.getSrcFile ());
      }
      else if (conf::getOptionValue (conf::opt_tpl))
      {
        printer.printDefn (out.getTplFile ());
      }
      else
      {
        printer.printDefn (out.getHdrFile ());
      }
    }
  }
}
#undef LZZ_INLINE
