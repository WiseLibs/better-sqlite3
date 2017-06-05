// smtc_TmplClassDefn.h
//

#ifndef LZZ_smtc_TmplClassDefn_h
#define LZZ_smtc_TmplClassDefn_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_TmplClassDecl.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplClassDefn : public TmplClassDecl
  {
  public:
    TmplClassDefn (TmplSpecPtrVector const & tmpl_spec_set, ClassDefnPtr const & class_defn);
    ~ TmplClassDefn ();
    ClassDefnPtr getClassDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplClassDefn.inl"
#endif
#endif
