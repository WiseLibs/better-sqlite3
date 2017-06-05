// smtc_TmplLazyClassPtr.h
//

#ifndef LZZ_smtc_TmplLazyClassPtr_h
#define LZZ_smtc_TmplLazyClassPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplClassDecl;
}
namespace smtc
{
  class TmplLazyClass;
}
namespace smtc
{
  typedef util::DPtr <TmplLazyClass, TmplClassDecl> TmplLazyClassPtr;
}
#undef LZZ_INLINE
#endif
