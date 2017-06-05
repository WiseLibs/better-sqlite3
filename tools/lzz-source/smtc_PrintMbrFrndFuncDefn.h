// smtc_PrintMbrFrndFuncDefn.h
//

#ifndef LZZ_smtc_PrintMbrFrndFuncDefn_h
#define LZZ_smtc_PrintMbrFrndFuncDefn_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_FuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndFuncDefn (FilePtr const & file, FuncDefnPtr const & func_defn);
}
#undef LZZ_INLINE
#endif
