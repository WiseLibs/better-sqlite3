// smtc_CreateClassInstEntity.h
//

#ifndef LZZ_smtc_CreateClassInstEntity_h
#define LZZ_smtc_CreateClassInstEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_ClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createClassInstEntity (ClassDeclPtr const & class_decl);
}
#undef LZZ_INLINE
#endif
