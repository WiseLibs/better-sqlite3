// smtc_CreateTdef.cpp
//

#include "smtc_CreateTdef.h"
// semantic
#include "smtc_Tdef.h"
#define LZZ_INLINE inline
namespace smtc
{
  TdefPtr createTdef (Linkage const & linkage, CvType const & cv_type, NamePtr const & name)
  {
    return new Tdef (linkage, cv_type, name);
  }
}
#undef LZZ_INLINE
