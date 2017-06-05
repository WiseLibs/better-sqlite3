// smtc_PrintNsTmplFuncDefn.h
//

#ifndef LZZ_smtc_PrintNsTmplFuncDefn_h
#define LZZ_smtc_PrintNsTmplFuncDefn_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_Output.h"
#include "smtc_TmplFuncDeclPtr.h"
#include "smtc_TmplFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsTmplFuncDefn (Output & out, TmplFuncDefnPtr const & tmpl_func_defn, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
