// smtc_CreateVdfClassEntity.cpp
//

#include "smtc_CreateVdfClassEntity.h"
// semantic
#include "smtc_VdfClassEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createVdfClassEntity (ClassDefnPtr const & class_defn)
  {
    return new VdfClassEntity (class_defn);
  }
}
#undef LZZ_INLINE
