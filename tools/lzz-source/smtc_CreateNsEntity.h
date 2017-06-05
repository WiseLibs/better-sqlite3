// smtc_CreateNsEntity.h
//

#ifndef LZZ_smtc_CreateNsEntity_h
#define LZZ_smtc_CreateNsEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createNsEntity (NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
