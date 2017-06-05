// smtc_TmplFuncDecl.cpp
//

#include "smtc_TmplFuncDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplFuncDecl.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  TmplFuncDecl::TmplFuncDecl (TmplSpecPtrVector const & tmpl_spec_set, FuncDeclPtr const & func_decl)
    : m_tmpl_spec_set (tmpl_spec_set), m_func_decl (func_decl)
    {}
}
namespace smtc
{
  TmplFuncDecl::~ TmplFuncDecl ()
    {}
}
#undef LZZ_INLINE
