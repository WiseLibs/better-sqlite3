// smtc_PrintTmplFuncDefn.h
//

#ifndef LZZ_smtc_PrintTmplFuncDefn_h
#define LZZ_smtc_PrintTmplFuncDefn_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_PrintFuncDefn.h"
#include "smtc_TmplFuncDefnPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintTmplFuncDefn : PrintFuncDefn
  {
    PrintTmplFuncDefn (NamePtr const & qual_name = NamePtr ());
    void print (FilePtr const & file, SectionKind skind, TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns);
    void print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns);
    void print (FilePtr const & file, SectionKind skind, TmplFuncDefnPtr const & tmpl_func_defn);
    void print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplFuncDefn.inl"
#endif
#endif
