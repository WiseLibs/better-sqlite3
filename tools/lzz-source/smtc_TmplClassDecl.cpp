// smtc_TmplClassDecl.cpp
//

#include "smtc_TmplClassDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplClassDecl.inl"
#endif
// semantic
#define LZZ_INLINE inline
namespace smtc
{
  TmplClassDecl::TmplClassDecl (TmplSpecPtrVector const & tmpl_spec_set, ClassDeclPtr const & class_decl)
    : m_tmpl_spec_set (tmpl_spec_set), m_class_decl (class_decl)
    {}
}
namespace smtc
{
  TmplClassDecl::~ TmplClassDecl ()
    {}
}
#undef LZZ_INLINE
