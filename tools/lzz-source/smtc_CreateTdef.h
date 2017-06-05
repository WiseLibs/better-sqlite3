// smtc_CreateTdef.h
//

#ifndef LZZ_smtc_CreateTdef_h
#define LZZ_smtc_CreateTdef_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_TdefPtr.h"
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
  TdefPtr createTdef (Linkage const & linkage, CvType const & cv_type, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
