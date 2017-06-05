// smtc_CreateObj.h
//

#ifndef LZZ_smtc_CreateObj_h
#define LZZ_smtc_CreateObj_h
// semantic
#include "smtc_InitPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Linkage;
}
namespace smtc
{
  class CvType;
}
namespace smtc
{
  ObjPtr createObj (int flags, CvType const & cv_type, NamePtr const & name, InitPtr const & init);
}
namespace smtc
{
  ObjPtr createObj (Linkage const & linkage, int flags, CvType const & cv_type, NamePtr const & name, InitPtr const & init);
}
#undef LZZ_INLINE
#endif
