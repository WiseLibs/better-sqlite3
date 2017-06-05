// smtc_CreateClassDefnEntity.h
//

#ifndef LZZ_smtc_CreateClassDefnEntity_h
#define LZZ_smtc_CreateClassDefnEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_ClassDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createClassDefnEntity (ClassDefnPtr const & class_defn);
}
#undef LZZ_INLINE
#endif
