// smtc_CreateFrndClassDeclEntity.cpp
//

#include "smtc_CreateFrndClassDeclEntity.h"
// semantic
#include "smtc_FrndClassDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndClassDeclEntity (ClassDeclPtr const & class_decl)
  {
    return new FrndClassDeclEntity (class_decl);
  }
}
#undef LZZ_INLINE
