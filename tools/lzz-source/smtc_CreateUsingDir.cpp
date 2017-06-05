// smtc_CreateUsingDir.cpp
//

#include "smtc_CreateUsingDir.h"
// semantic
#include "smtc_UsingDir.h"
#define LZZ_INLINE inline
namespace smtc
{
  UsingDirPtr createUsingDir (NamePtr const & name)
  {
    return new UsingDir (name);
  }
}
#undef LZZ_INLINE
