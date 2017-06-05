// smtc_TmplFuncDeclPtr.h
//

#ifndef LZZ_smtc_TmplFuncDeclPtr_h
#define LZZ_smtc_TmplFuncDeclPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplFuncDecl;
}
namespace smtc
{
  typedef util::BPtr <TmplFuncDecl> TmplFuncDeclPtr;
}
#undef LZZ_INLINE
#endif
