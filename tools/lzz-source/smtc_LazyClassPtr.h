// smtc_LazyClassPtr.h
//

#ifndef LZZ_smtc_LazyClassPtr_h
#define LZZ_smtc_LazyClassPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDecl;
}
namespace smtc
{
  class LazyClass;
}
namespace smtc
{
  typedef util::DPtr <LazyClass, ClassDecl> LazyClassPtr;
}
#undef LZZ_INLINE
#endif
