// smtc_CreateObjEntity.cpp
//

#include "smtc_CreateObjEntity.h"
// semantic
#include "smtc_ObjEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createObjEntity (ObjPtr const & obj)
  {
    return new ObjEntity (obj);
  }
}
#undef LZZ_INLINE
