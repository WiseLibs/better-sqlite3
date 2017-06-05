// smtc_CreateClassDeclEntity.cpp
//

#include "smtc_CreateClassDeclEntity.h"
// semantic
#include "smtc_ClassDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createClassDeclEntity (ClassDeclPtr const & class_decl)
  {
    return new ClassDeclEntity (class_decl);
  }
}
#undef LZZ_INLINE
