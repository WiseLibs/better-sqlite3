// smtc_CreateObj.cpp
//

#include "smtc_CreateObj.h"
// semantic
#include "smtc_Obj.h"
#define LZZ_INLINE inline
namespace smtc
{
  ObjPtr createObj (int flags, CvType const & cv_type, NamePtr const & name, InitPtr const & init)
  {
    return new Obj (Linkage (), flags, cv_type, name, init);
  }
}
namespace smtc
{
  ObjPtr createObj (Linkage const & linkage, int flags, CvType const & cv_type, NamePtr const & name, InitPtr const & init)
  {
    return new Obj (linkage, flags, cv_type, name, init);
  }
}
#undef LZZ_INLINE
