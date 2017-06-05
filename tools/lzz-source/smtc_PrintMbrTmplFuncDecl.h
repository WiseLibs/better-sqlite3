// smtc_PrintMbrTmplFuncDecl.h
//

#ifndef LZZ_smtc_PrintMbrTmplFuncDecl_h
#define LZZ_smtc_PrintMbrTmplFuncDecl_h
// semantic
#include "smtc_TmplFuncDeclPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplFuncDecl (FilePtr const & file, TmplFuncDeclPtr const & tmpl_func_decl);
}
#undef LZZ_INLINE
#endif
