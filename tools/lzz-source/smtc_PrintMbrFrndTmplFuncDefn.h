// smtc_PrintMbrFrndTmplFuncDefn.h
//

#ifndef LZZ_smtc_PrintMbrFrndTmplFuncDefn_h
#define LZZ_smtc_PrintMbrFrndTmplFuncDefn_h
// semantic
#include "smtc_TmplFuncDefnPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printMbrFrndTmplFuncDefn (FilePtr const & file, TmplFuncDefnPtr const & tmpl_func_defn);
}
#undef LZZ_INLINE
#endif
