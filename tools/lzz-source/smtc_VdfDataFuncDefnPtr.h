// smtc_VdfDataFuncDefnPtr.h
//

#ifndef LZZ_smtc_VdfDataFuncDefnPtr_h
#define LZZ_smtc_VdfDataFuncDefnPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDecl;
}
namespace smtc
{
  class VdfDataFuncDefn;
}
namespace smtc
{
  typedef util::DPtr <VdfDataFuncDefn, FuncDecl> VdfDataFuncDefnPtr;
}
#undef LZZ_INLINE
#endif
