// smtc_CreateClassDefnEntity.cpp
//

#include "smtc_CreateClassDefnEntity.h"
// semantic
#include "smtc_ClassDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createClassDefnEntity (ClassDefnPtr const & class_defn)
  {
    return new ClassDefnEntity (class_defn);
  }
}
#undef LZZ_INLINE
