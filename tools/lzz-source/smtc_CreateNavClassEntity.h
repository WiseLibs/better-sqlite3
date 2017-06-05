// smtc_CreateNavClassEntity.h
//

#ifndef LZZ_smtc_CreateNavClassEntity_h
#define LZZ_smtc_CreateNavClassEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_NavClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createNavClassEntity (NavClassPtr const & nav_class);
}
#undef LZZ_INLINE
#endif
