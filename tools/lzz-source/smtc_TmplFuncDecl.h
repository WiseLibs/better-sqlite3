// smtc_TmplFuncDecl.h
//

#ifndef LZZ_smtc_TmplFuncDecl_h
#define LZZ_smtc_TmplFuncDecl_h
// semantic
#include "smtc_FuncDeclPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplFuncDecl
  {
    TmplSpecPtrVector m_tmpl_spec_set;
    FuncDeclPtr m_func_decl;
  public:
    TmplFuncDecl (TmplSpecPtrVector const & tmpl_spec_set, FuncDeclPtr const & func_decl);
    ~ TmplFuncDecl ();
    TmplSpecPtrVector const & getTmplSpecSet () const;
    FuncDeclPtr const & getFuncDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplFuncDecl.inl"
#endif
#endif
