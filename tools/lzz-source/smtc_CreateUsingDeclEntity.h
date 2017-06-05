// smtc_CreateUsingDeclEntity.h
//

#ifndef LZZ_smtc_CreateUsingDeclEntity_h
#define LZZ_smtc_CreateUsingDeclEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_UsingDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createUsingDeclEntity (UsingDeclPtr const & using_decl);
}
#undef LZZ_INLINE
#endif
