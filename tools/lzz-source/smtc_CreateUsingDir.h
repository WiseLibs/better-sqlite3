// smtc_CreateUsingDir.h
//

#ifndef LZZ_smtc_CreateUsingDir_h
#define LZZ_smtc_CreateUsingDir_h
// semantic
#include "smtc_UsingDirPtr.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  UsingDirPtr createUsingDir (NamePtr const & name);
}
#undef LZZ_INLINE
#endif
