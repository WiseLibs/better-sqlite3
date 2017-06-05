// smtc_UsingDeclPtr.h
//

#ifndef LZZ_smtc_UsingDeclPtr_h
#define LZZ_smtc_UsingDeclPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UsingDecl;
}
namespace smtc
{
  typedef util::BPtr <UsingDecl> UsingDeclPtr;
}
#undef LZZ_INLINE
#endif
