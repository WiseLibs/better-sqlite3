// smtc_PrintTmplFuncDecl.cpp
//

#include "smtc_PrintTmplFuncDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplFuncDecl.inl"
#endif
// semantic
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_PrintTmplSpecSet.h"
#include "smtc_TmplFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void PrintTmplFuncDecl::print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns)
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, func_decl, tmpl_spec_set);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintTmplFuncDecl::print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl, TmplSpecPtrVector const & tmpl_spec_set)
    {
      printTmplSpecSet (file, skind, tmpl_spec_set, is_decl);
      PrintFuncDecl::print (file, skind, func_decl);
    }
}
namespace smtc
{
  void PrintTmplFuncDecl::print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns)
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, tmpl_func_decl, tmpl_spec_set);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintTmplFuncDecl::print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl, TmplSpecPtrVector const & tmpl_spec_set)
    {
      printTmplSpecSet (file, skind, tmpl_spec_set, is_decl);
      print (file, skind, tmpl_func_decl->getFuncDecl (), tmpl_func_decl->getTmplSpecSet ());
    }
}
#undef LZZ_INLINE
