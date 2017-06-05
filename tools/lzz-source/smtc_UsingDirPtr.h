// smtc_UsingDirPtr.h
//

#ifndef LZZ_smtc_UsingDirPtr_h
#define LZZ_smtc_UsingDirPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UsingDir;
}
namespace smtc
{
  typedef util::BPtr <UsingDir> UsingDirPtr;
}
#undef LZZ_INLINE
#endif
