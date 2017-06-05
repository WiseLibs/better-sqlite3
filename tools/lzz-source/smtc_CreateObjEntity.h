// smtc_CreateObjEntity.h
//

#ifndef LZZ_smtc_CreateObjEntity_h
#define LZZ_smtc_CreateObjEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createObjEntity (ObjPtr const & obj);
}
#undef LZZ_INLINE
#endif
