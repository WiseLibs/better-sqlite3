// smtc_FuncDefnPtr.h
//

#ifndef LZZ_smtc_FuncDefnPtr_h
#define LZZ_smtc_FuncDefnPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDecl;
}
namespace smtc
{
  class FuncDefn;
}
namespace smtc
{
  typedef util::DPtr <FuncDefn, FuncDecl> FuncDefnPtr;
}
#undef LZZ_INLINE
#endif
