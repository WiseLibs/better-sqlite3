// smtc_PrintMbrTmplFuncDefn.h
//

#ifndef LZZ_smtc_PrintMbrTmplFuncDefn_h
#define LZZ_smtc_PrintMbrTmplFuncDefn_h
// semantic
#include "smtc_FuncDefnPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_TmplFuncDefnPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printMbrTmplFuncDefn (Output & out, TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns, NamePtr const & qual_name);
}
namespace smtc
{
  void printMbrTmplFuncDefn (Output & out, TmplFuncDefnPtr const & tmpl_func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name);
}
namespace smtc
{
  void printMbrTmplFuncDefn (Output & out, FuncDefnPtr const & func_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name);
}
#undef LZZ_INLINE
#endif
