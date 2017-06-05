// smtc_TmplClassDeclPtr.h
//

#ifndef LZZ_smtc_TmplClassDeclPtr_h
#define LZZ_smtc_TmplClassDeclPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplClassDecl;
}
namespace smtc
{
  typedef util::BPtr <TmplClassDecl> TmplClassDeclPtr;
}
#undef LZZ_INLINE
#endif
