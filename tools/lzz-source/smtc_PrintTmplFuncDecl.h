// smtc_PrintTmplFuncDecl.h
//

#ifndef LZZ_smtc_PrintTmplFuncDecl_h
#define LZZ_smtc_PrintTmplFuncDecl_h
// semantic
#include "smtc_PrintFuncDecl.h"
#include "smtc_TmplFuncDeclPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintTmplFuncDecl : PrintFuncDecl
  {
    PrintTmplFuncDecl (NamePtr const & qual_name = NamePtr ());
    void print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns);
    void print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl, TmplSpecPtrVector const & tmpl_spec_set);
    void print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns);
    void print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl, TmplSpecPtrVector const & tmpl_spec_set);
    void print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl, NsPtr const & ns);
    void print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplFuncDecl.inl"
#endif
#endif
