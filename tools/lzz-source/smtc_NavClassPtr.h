// smtc_NavClassPtr.h
//

#ifndef LZZ_smtc_NavClassPtr_h
#define LZZ_smtc_NavClassPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDecl;
}
namespace smtc
{
  class NavClass;
}
namespace smtc
{
  typedef util::DPtr <NavClass, ClassDecl> NavClassPtr;
}
#undef LZZ_INLINE
#endif
