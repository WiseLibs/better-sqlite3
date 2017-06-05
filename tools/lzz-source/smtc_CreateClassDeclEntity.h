// smtc_CreateClassDeclEntity.h
//

#ifndef LZZ_smtc_CreateClassDeclEntity_h
#define LZZ_smtc_CreateClassDeclEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_ClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createClassDeclEntity (ClassDeclPtr const & class_decl);
}
#undef LZZ_INLINE
#endif
