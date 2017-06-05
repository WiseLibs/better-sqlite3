// smtc_PrintMbrFuncDecl.h
//

#ifndef LZZ_smtc_PrintMbrFuncDecl_h
#define LZZ_smtc_PrintMbrFuncDecl_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_FuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFuncDecl (FilePtr const & file, FuncDeclPtr const & func_decl);
}
#undef LZZ_INLINE
#endif
