// smtc_FuncDeclPtr.h
//

#ifndef LZZ_smtc_FuncDeclPtr_h
#define LZZ_smtc_FuncDeclPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDecl;
}
namespace smtc
{
  typedef util::BPtr <FuncDecl> FuncDeclPtr;
}
#undef LZZ_INLINE
#endif
