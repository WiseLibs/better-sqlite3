// smtc_CreateUsingDirEntity.h
//

#ifndef LZZ_smtc_CreateUsingDirEntity_h
#define LZZ_smtc_CreateUsingDirEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_UsingDirPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createUsingDirEntity (UsingDirPtr const & using_dir);
}
#undef LZZ_INLINE
#endif
