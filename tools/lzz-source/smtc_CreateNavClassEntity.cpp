// smtc_CreateNavClassEntity.cpp
//

#include "smtc_CreateNavClassEntity.h"
// semantic
#include "smtc_NavClassEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createNavClassEntity (NavClassPtr const & nav_class)
  {
    return new NavClassEntity (nav_class);
  }
}
#undef LZZ_INLINE
