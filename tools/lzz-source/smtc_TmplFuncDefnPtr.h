// smtc_TmplFuncDefnPtr.h
//

#ifndef LZZ_smtc_TmplFuncDefnPtr_h
#define LZZ_smtc_TmplFuncDefnPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplFuncDecl;
}
namespace smtc
{
  class TmplFuncDefn;
}
namespace smtc
{
  typedef util::DPtr <TmplFuncDefn, TmplFuncDecl> TmplFuncDefnPtr;
}
#undef LZZ_INLINE
#endif
