// smtc_CreateFrndClassDeclEntity.h
//

#ifndef LZZ_smtc_CreateFrndClassDeclEntity_h
#define LZZ_smtc_CreateFrndClassDeclEntity_h
// semantic
#include "smtc_ClassDeclPtr.h"
#include "smtc_EntityPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndClassDeclEntity (ClassDeclPtr const & class_decl);
}
#undef LZZ_INLINE
#endif
