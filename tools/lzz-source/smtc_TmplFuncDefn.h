// smtc_TmplFuncDefn.h
//

#ifndef LZZ_smtc_TmplFuncDefn_h
#define LZZ_smtc_TmplFuncDefn_h
// semantic
#include "smtc_FuncDefnPtr.h"
#include "smtc_TmplFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplFuncDefn : public TmplFuncDecl
  {
  public:
    TmplFuncDefn (TmplSpecPtrVector const & tmpl_spec_set, FuncDefnPtr const & func_defn);
    ~ TmplFuncDefn ();
    FuncDefnPtr getFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplFuncDefn.inl"
#endif
#endif
