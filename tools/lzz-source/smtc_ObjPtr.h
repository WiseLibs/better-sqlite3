// smtc_ObjPtr.h
//

#ifndef LZZ_smtc_ObjPtr_h
#define LZZ_smtc_ObjPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Obj;
}
namespace smtc
{
  typedef util::BPtr <Obj> ObjPtr;
}
#undef LZZ_INLINE
#endif
