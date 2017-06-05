// smtc_PrintMbrFuncDefn.cpp
//

#include "smtc_PrintMbrFuncDefn.h"
// semantic
#include "smtc_FuncDefn.h"
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
    NamePtr const & qual_name;
    void printDefn (FilePtr const & file, SectionKind skind = BODY_SECTION);
  public:
    explicit Printer (FuncDefnPtr const & func_defn, NsPtr const & ns, NamePtr const & qual_name);
    ~ Printer ();
  };
}
namespace
{
  void Printer::printDefn (FilePtr const & file, SectionKind skind)
    {
      PrintFuncDefn printer (qual_name);
      printer.not_static = true;
      printer.not_explicit = true;
      printer.not_virtual = true;
      printer.not_pure = true;
      printer.use_alt_ret_type = true;
      printer.print (file, skind, func_defn, ns);
    }
}
namespace
{
  LZZ_INLINE Printer::Printer (FuncDefnPtr const & func_defn, NsPtr const & ns, NamePtr const & qual_name)
    : func_defn (func_defn), ns (ns), qual_name (qual_name)
         {}
}
namespace
{
  Printer::~ Printer ()
         {}
}
namespace smtc
{
  void printMbrFuncDefn (Output & out, FuncDefnPtr const & func_defn, NsPtr const & ns, NamePtr const & qual_name)
  {
    Printer printer (func_defn, ns, qual_name);
    if (! func_defn->isInline () || isNsEnclUnmd (ns))
    {
      printer.printDefn (out.getSrcFile ());
    }
    else if (conf::getOptionValue (conf::opt_inl_inl))
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
}
#undef LZZ_INLINE
