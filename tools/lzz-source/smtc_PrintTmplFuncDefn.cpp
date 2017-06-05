// smtc_PrintTmplFuncDefn.cpp
//

#include "smtc_PrintTmplFuncDefn.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplFuncDefn.inl"
#endif
// semantic
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_PrintTmplSpecSet.h"
#include "smtc_TmplFuncDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void PrintTmplFuncDefn::print (FilePtr const & file, SectionKind skind, TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns)
    {
      print (file, skind, tmpl_func_defn->getFuncDefn (), tmpl_func_defn->getTmplSpecSet (), ns);
    }
}
namespace smtc
{
  void PrintTmplFuncDefn::print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns)
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, func_defn, tmpl_spec_set);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintTmplFuncDefn::print (FilePtr const & file, SectionKind skind, TmplFuncDefnPtr const & tmpl_func_defn)
    {
      print (file, skind, tmpl_func_defn->getFuncDefn (), tmpl_func_defn->getTmplSpecSet ());
    }
}
namespace smtc
{
  void PrintTmplFuncDefn::print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set)
    {
      printTmplSpecSet (file, skind, tmpl_spec_set, is_decl);
      PrintFuncDefn::print (file, skind, func_defn);
    }
}
#undef LZZ_INLINE
