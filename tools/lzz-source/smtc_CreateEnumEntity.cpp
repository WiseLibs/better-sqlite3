// smtc_CreateEnumEntity.cpp
//

#include "smtc_CreateEnumEntity.h"
// semantic
#include "smtc_EnumEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createEnumEntity (EnumPtr const & en)
  {
    return new EnumEntity (en);
  }
}
#undef LZZ_INLINE
