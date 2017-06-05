// smtc_FilePtr.h
//

#ifndef LZZ_smtc_FilePtr_h
#define LZZ_smtc_FilePtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class File;
}
namespace smtc
{
  typedef util::BPtr <File> FilePtr;
}
#undef LZZ_INLINE
#endif
