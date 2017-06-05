// smtc_NavSubmitFuncDefnPtr.h
//

#ifndef LZZ_smtc_NavSubmitFuncDefnPtr_h
#define LZZ_smtc_NavSubmitFuncDefnPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDecl;
}
namespace smtc
{
  class NavSubmitFuncDefn;
}
namespace smtc
{
  typedef util::DPtr <NavSubmitFuncDefn, FuncDecl> NavSubmitFuncDefnPtr;
}
#undef LZZ_INLINE
#endif
