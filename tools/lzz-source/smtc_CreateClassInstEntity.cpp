// smtc_CreateClassInstEntity.cpp
//

#include "smtc_CreateClassInstEntity.h"
// semantic
#include "smtc_ClassInstEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createClassInstEntity (ClassDeclPtr const & class_decl)
  {
    return new ClassInstEntity (class_decl);
  }
}
#undef LZZ_INLINE
