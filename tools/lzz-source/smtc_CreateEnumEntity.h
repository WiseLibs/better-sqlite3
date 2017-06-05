// smtc_CreateEnumEntity.h
//

#ifndef LZZ_smtc_CreateEnumEntity_h
#define LZZ_smtc_CreateEnumEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_EnumPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createEnumEntity (EnumPtr const & en);
}
#undef LZZ_INLINE
#endif
