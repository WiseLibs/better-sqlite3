// smtc_TmplClassDefnPtr.h
//

#ifndef LZZ_smtc_TmplClassDefnPtr_h
#define LZZ_smtc_TmplClassDefnPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplClassDecl;
}
namespace smtc
{
  class TmplClassDefn;
}
namespace smtc
{
  typedef util::DPtr <TmplClassDefn, TmplClassDecl> TmplClassDefnPtr;
}
#undef LZZ_INLINE
#endif
