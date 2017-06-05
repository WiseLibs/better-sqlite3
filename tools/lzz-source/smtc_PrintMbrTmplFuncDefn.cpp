// smtc_PrintMbrTmplFuncDefn.cpp
//

#include "smtc_PrintMbrTmplFuncDefn.h"
// semantic
#include "smtc_FuncDefn.h"
#include "smtc_IsExplicitTmplSpec.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
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
    FuncDefnPtr const & func_defn;
    TmplSpecPtrVector const & tmpl_spec_set;
    NsPtr const & ns;
    NamePtr const & qual_name;
    void printDefn (FilePtr const & file, SectionKind skind = BODY_SECTION);
  public:
    explicit Printer (FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name);
    ~ Printer ();
  };
}
namespace
{
  void Printer::printDefn (FilePtr const & file, SectionKind skind)
    {
      PrintTmplFuncDefn printer (qual_name);
      printer.not_static = true;
      printer.not_explicit = true;
      printer.not_virtual = true;
      printer.not_pure = true;
      printer.use_alt_ret_type = true;
      printer.print (file, skind, func_defn, tmpl_spec_set, ns);
    }
}
namespace
{
  LZZ_INLINE Printer::Printer (FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name)
    : func_defn (func_defn), tmpl_spec_set (tmpl_spec_set), ns (ns), qual_name (qual_name)
         {}
}
namespace
{
  Printer::~ Printer ()
         {}
}
namespace smtc
{
  void printMbrTmplFuncDefn (Output & out, TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns, NamePtr const & qual_name)
  {
    printMbrTmplFuncDefn (out, tmpl_func_defn->getFuncDefn (), tmpl_func_defn->getTmplSpecSet (), ns, qual_name);
  }
}
namespace smtc
{
  void printMbrTmplFuncDefn (Output & out, TmplFuncDefnPtr const & tmpl_func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name)
  {
    TmplSpecPtrVector full_tmpl_spec_set (tmpl_func_defn->getTmplSpecSet ());
    full_tmpl_spec_set.insert (full_tmpl_spec_set.end (), tmpl_spec_set.begin (), tmpl_spec_set.end ());
    printMbrTmplFuncDefn (out, tmpl_func_defn->getFuncDefn (), full_tmpl_spec_set, ns, qual_name);
  }
}
namespace smtc
{
  void printMbrTmplFuncDefn (Output & out, FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name)
  {
    // get file
    Printer printer (func_defn, tmpl_spec_set, ns, qual_name);
    if (isNsEnclUnmd (ns))
    {
      printer.printDefn (out.getSrcFile ());
    }
    else
    {
      // we want to do the same thing as an explicit spec if we're outputting tpl code to source
      bool is_expl_spec = isExplicitTmplSpec (tmpl_spec_set) || conf::getOptionValue (conf::opt_tpl_src);
      if (func_defn->isInline ())
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
