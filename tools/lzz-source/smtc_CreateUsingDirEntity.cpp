// smtc_CreateUsingDirEntity.cpp
//

#include "smtc_CreateUsingDirEntity.h"
// semantic
#include "smtc_UsingDirEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createUsingDirEntity (UsingDirPtr const & using_dir)
  {
    return new UsingDirEntity (using_dir);
  }
}
#undef LZZ_INLINE
