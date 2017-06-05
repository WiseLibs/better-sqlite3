// smtc_CreateVdfClassEntity.h
//

#ifndef LZZ_smtc_CreateVdfClassEntity_h
#define LZZ_smtc_CreateVdfClassEntity_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_EntityPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createVdfClassEntity (ClassDefnPtr const & class_defn);
}
#undef LZZ_INLINE
#endif
