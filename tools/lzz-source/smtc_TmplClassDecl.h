// smtc_TmplClassDecl.h
//

#ifndef LZZ_smtc_TmplClassDecl_h
#define LZZ_smtc_TmplClassDecl_h
// semantic
#include "smtc_ClassDeclPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplClassDecl
  {
    TmplSpecPtrVector m_tmpl_spec_set;
    ClassDeclPtr m_class_decl;
  public:
    TmplClassDecl (TmplSpecPtrVector const & tmpl_spec_set, ClassDeclPtr const & class_decl);
    ~ TmplClassDecl ();
    TmplSpecPtrVector const & getTmplSpecSet () const;
    ClassDeclPtr const & getClassDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplClassDecl.inl"
#endif
#endif
